#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct Edge {
  Edge(int neighbor, int length) {
    this->neighbor = neighbor;
    this->length = length;
    this->next = -1;
  }
  int neighbor;
  int length;
  int next;
};

struct Graph {
  Graph(int num_nodes, int expected_num_edges) : head(num_nodes, -1) {
    edges.reserve(expected_num_edges);
  }

  void AddEdge(int x, int y, int len) {
    Edge e(y, len);
    e.next = head[x];
    head[x] = edges.size();
    edges.push_back(e);
  }

  vector<Edge> edges;
  vector<int> head;
};

struct TrieNode {
  TrieNode() {
    children[0] = NULL;
    children[1] = NULL;
  }

  TrieNode* children[2];
};

struct Trie {
  Trie(int expected_num_nodes, int bw) : bit_width(bw) {
    nodes.reserve(expected_num_nodes);
    nodes.resize(1);
  }

  void Insert(int number) {
    TrieNode* p = &nodes[0];
    for (int i = bit_width - 1; i >= 0; --i) {
      int bit = (number >> i) & 1;
      TrieNode *&child = p->children[bit];
      if (child == NULL) {
        nodes.resize(nodes.size() + 1);
        child = &nodes.back();
      }
      p = child;
    }
  }

  int FindClosest(int number) {
    int closest = 0;
    TrieNode* p = &nodes[0];
    for (int i = bit_width - 1; i >= 0; --i) {
      int bit = (number >> i) & 1;
      if (p->children[bit] == NULL) {
        bit = 1 - bit;
      }
      closest = closest * 2 + bit;
      p = p->children[bit];
    }
    return closest;
  }

  vector<TrieNode> nodes;
  int bit_width;
};

void DFS(const Graph &g, vector<int> *stack, vector<int> *parent,
         vector<int> *prefix_xor) {
  while (!stack->empty()) {
    int x = stack->back();
    stack->pop_back();
    int i = g.head[x];
    while (i != -1) {
      const Edge& e = g.edges[i];
      int y = e.neighbor;
      if ((*parent)[y] == -1) {
        stack->push_back(y);
        (*parent)[y] = x;
        (*prefix_xor)[y] = (*prefix_xor)[x] ^ e.length;
      }
      i = e.next;
    }
  }
}

int BitWidth(int number) {
  int bit_width = 0;
  while (number > 0) {
    number /= 2;
    bit_width++;
  }
  return bit_width;
}

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    Graph g(n, n * 2);
    for (int i = 0; i < n - 1; ++i) {
      int x, y, len;
      scanf("%d %d %d", &x, &y, &len);
      g.AddEdge(x, y, len);
      g.AddEdge(y, x, len);
    }

    vector<int> stack;
    vector<int> parent(n, -1);
    vector<int> prefix_xor(n);

    stack.push_back(0);
    parent[0] = 0;
    prefix_xor[0] = 0;
    DFS(g, &stack, &parent, &prefix_xor);

    // The height of the trie doesn't need to exceed the bit width of the
    // largest possible xor value.
    int bit_width =
        BitWidth(*max_element(prefix_xor.begin(), prefix_xor.end()));
    Trie trie(n * bit_width, bit_width);
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
