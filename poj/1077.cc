#include <iostream>
#include <queue>

using namespace std;

const int n = 3;
int power_of_tens[n * n];
int factorial[n * n + 1];

int FindZero(int b) {
  for (int i = 0; i < n * n; ++i) {
    if (b % 10 == 0) {
      return i;
    }
    b /= 10;
  }
}

int DigitAtIndex(int number, int i) { return number / power_of_tens[i] % 10; }

int Compress(int b) {
  int compressed = 0;
  int seen_digits = 0;
  for (int i = 0; i < n * n; ++i) {
    int digit = b % 10;
    int num_unseen_digits_before = 0;
    for (int j = 0; j < digit; ++j) {
      if ((seen_digits & (1 << j)) == 0) {
        num_unseen_digits_before++;
      }
    }
    compressed += num_unseen_digits_before * factorial[n * n - 1 - i];
    seen_digits |= (1 << digit);
    b /= 10;
  }
  return compressed;
}

bool BFS(int start, int end, vector<pair<int, char> >* pre) {
  queue<int> q;

  q.push(start);
  (*pre)[Compress(start)] = make_pair(start, ' ');

  pair<int, char> neighbors[4];
  while (!q.empty()) {
    int b = q.front();
    q.pop();
    if (b == end) {
      return true;
    }

    int zero_pos = FindZero(b);
    int x = zero_pos / n;
    int y = zero_pos % n;

    int num_neighbors = 0;
    if (x > 0) {
      neighbors[num_neighbors++] =
          make_pair(Swap(b, zero_pos, zero_pos - n), 'u');
    }
    if (x + 1 < n) {
      neighbors[num_neighbors++] =
          make_pair(Swap(b, zero_pos, zero_pos + n), 'd');
    }
    if (y > 0) {
      neighbors[num_neighbors++] =
          make_pair(Swap(b, zero_pos, zero_pos - 1), 'l');
    }
    if (y + 1 < n) {
      neighbors[num_neighbors++] =
          make_pair(Swap(b, zero_pos, zero_pos + 1), 'r');
    }
    for (int i = 0; i < num_neighbors; ++i) {
      int neighbor = neighbors[i].first;
      char op = neighbors[i].second;
      int compressed = Compress(neighbor);
      if ((*pre)[compressed].first == -1) {
        q.push(neighbor);
        (*pre)[compressed] = make_pair(b, op);
      }
    }
  }
  return false;
}

int main() {
  power_of_tens[0] = 1;
  for (int i = 1; i < n * n; ++i) {
    power_of_tens[i] = power_of_tens[i - 1] * 10;
  }
  factorial[0] = 1;
  for (int i = 1; i <= n * n; ++i) {
    factorial[i] = factorial[i - 1] * i;
  }

  int start = 0;
  for (int i = 0; i < n * n; ++i) {
    char ch;
    cin >> ch;
    if (ch == 'x') {
      ch = '0';
    }
    start += power_of_tens[i] * (ch - '0');
  }

  int end = 0;
  for (int i = 0; i < n * n - 1; ++i) {
    end += power_of_tens[i] * (i + 1);
  }

  vector<pair<int, char> > pre(factorial[n * n], make_pair(-1, ' '));
  if (!BFS(start, end, &pre)) {
    cout << "unsolvable" << endl;
    return 0;
  }

  vector<char> ops;
  int b = end;
  while (b != start) {
    int compressed = Compress(b);
    ops.push_back(pre[compressed].second);
    b = pre[compressed].first;
  }
  for (int i = (int)ops.size() - 1; i >= 0; --i) {
    cout << ops[i];
  }
  cout << endl;
}
