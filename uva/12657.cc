#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int value;
  Node* prev;
  Node* next;
};

void InsertBefore(Node* cur, Node* pos) {
  Node* prev = pos->prev;
  prev->next = cur;
  cur->prev = prev;
  cur->next = pos;
  pos->prev = cur;
}

void Detach(Node* pos) {
  Node* prev = pos->prev;
  Node* next = pos->next;
  prev->next = next;
  next->prev = prev;
}

void Erase(Node* pos) {
  Detach(pos);
  delete pos;
}

void MoveBefore(Node* cur, Node* pos) {
  Detach(cur);
  InsertBefore(cur, pos);
}

int main() {
  Node* head = new Node();
  Node* tail = new Node();
  head->prev = NULL;
  head->next = tail;
  tail->prev = head;
  tail->next = NULL;

  int n, m;
  int case_id = 0;
  while (cin >> n >> m) {
    vector<Node*> pos(n + 1);
    for (int x = 1; x <= n; ++x) {
      Node* cur = new Node();
      cur->value = x;
      InsertBefore(cur, tail);
      pos[x] = cur;
    }

    bool reversed = false;
    for (int i = 0; i < m; ++i) {
      int op;
      cin >> op;
      if (op == 1 || op == 2) {
        if (reversed) {
          op = 3 - op;
        }
        int x, y;
        cin >> x >> y;
        // We can't simply call MoveBefore. If y is right before x,
        // MoveBefore(pos[x], pos[y]->next) would cause a cycle.
        Detach(pos[x]);
        if (op == 1) {
          InsertBefore(pos[x], pos[y]);
        } else {
          InsertBefore(pos[x], pos[y]->next);
        }
      } else if (op == 3) {
        int x, y;
        cin >> x >> y;
        if (x == y) {
          continue;
        }
        if (pos[x]->next == pos[y] || pos[y]->next == pos[x]) {
          if (pos[y]->next == pos[x]) {
            swap(x, y);
          }
          // x must be before y at this point.
          MoveBefore(pos[x], pos[y]->next);
        } else {
          Node* x_next = pos[x]->next;
          Node* y_next = pos[y]->next;
          MoveBefore(pos[x], y_next);
          MoveBefore(pos[y], x_next);
        }
      } else {
        reversed = !reversed;
      }
    }

    long long sum = 0;
    if (!reversed) {
      Node* cur = head->next;
      while (cur) {
        sum += cur->value;
        cur = cur->next;
        if (cur) {
          cur = cur->next;
        }
      }
    } else {
      Node* cur = tail->prev;
      while (cur) {
        sum += cur->value;
        cur = cur->prev;
        if (cur) {
          cur = cur->prev;
        }
      }
    }
    case_id++;
    cout << "Case " << case_id << ": " << sum << endl;

    for (int x = 1; x <= n; ++x) {
      Erase(pos[x]);
    }
  }
}
