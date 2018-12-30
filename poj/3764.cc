#include <cstdio>
#include <vector>

using namespace std;

struct Edge {
  Edge(int neighbor, int length) {
    this->neighbor = neighbor;
    this->length = length;
  }
  int neighbor;
  int length;
};

typedef vector<vector<Edge> > Graph;

struct TrieNode {
  TrieNode() {
    children[0] = NULL;
    children[1] = NULL;
  }

  TrieNode* children[2];
};

struct Trie {
  Trie() {
    root = new TrieNode();
  }

  ~Trie() {
    Erase(root);
  }

  void Erase(TrieNode* p) {
    if (p == NULL) {
      return;
    }
    for (int i = 0; i < 2; ++i) {
      Erase(p->children[i]);
    }
    delete p;
  }

  void Insert(int number) {
    TrieNode* p = root;
    for (int i = 31; i >= 0; --i) {
      int bit = (number >> i) & 1;
      if (p->children[bit] == NULL) {
        TrieNode* q = new TrieNode();
        p->children[bit] = q;
      }
      p = p->children[bit];
    }
  }

  int FindClosest(int number) {
    int closest = 0;
    TrieNode* p = root;
    for (int i = 31; i >= 0; --i) {
      int bit = (number >> i) & 1;
      if (p->children[bit] == NULL) {
        bit = 1 - bit;
      }
      closest = closest * 2 + bit;
      p = p->children[bit];
    }
    return closest;
  }

  TrieNode* root;
};

void DFS(const Graph &g, vector<int> *stack, vector<int> *parent,
         vector<int> *prefix_xor) {
  while (!stack->empty()) {
    int x = stack->back();
    stack->pop_back();
    for (int i = 0; i < g[x].size(); ++i) {
      const Edge& e = g[x][i];
      int y = e.neighbor;
      if ((*parent)[y] == -1) {
        stack->push_back(y);
        (*parent)[y] = x;
        (*prefix_xor)[y] = (*prefix_xor)[x] ^ e.length;
      }
    }
  }
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    Graph g(n);
    for (int i = 0; i < n - 1; ++i) {
      int x, y, len;
      scanf("%d %d %d", &x, &y, &len);
      g[x].push_back(Edge(y, len));
      g[y].push_back(Edge(x, len));
    }

    vector<int> stack;
    vector<int> parent(n, -1);
    vector<int> prefix_xor(n);

    stack.push_back(0);
    parent[0] = 0;
    prefix_xor[0] = 0;
    DFS(g, &stack, &parent, &prefix_xor);

    Trie trie;
    trie.Insert(prefix_xor[0]);

    int max_xor = 0;
    for (int x = 1; x < n; ++x) {
      int cur = prefix_xor[x];
      int farthest = trie.FindClosest(~cur);
      max_xor = max(max_xor, farthest ^ cur);
      trie.Insert(cur);
    }
    printf("%d\n", max_xor);
  }
}
