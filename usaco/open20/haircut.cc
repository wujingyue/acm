#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int key;
  int count;
};

class BinarySearchTree {
 public:
  BinarySearchTree(int max_value) : nodes_(max_value + 1) {
    int next_to_fill = 0;
    Fill(0, &next_to_fill);
  }

  void Insert(const int x) {
    int i = 0;
    while (i < (int)nodes_.size()) {
      nodes_[i].count++;
      if (x == nodes_[i].key) {
        break;
      }
      if (x < nodes_[i].key) {
        i = i * 2 + 1;
      } else {
        i = i * 2 + 2;
      }
    }
  }

  int NumLargerThan(const int x) {
    int num_larger_than = 0;
    int i = 0;
    while (i < (int)nodes_.size()) {
      const int left = i * 2 + 1;
      const int right = i * 2 + 2;
      if (x < nodes_[i].key) {
        num_larger_than += nodes_[i].count -
                           (left < (int)nodes_.size() ? nodes_[left].count : 0);
        i = left;
      } else {
        i = right;
      }
    }
    return num_larger_than;
  }

 private:
  void Fill(const int i, int* next_to_fill) {
    if (i >= (int)nodes_.size()) {
      return;
    }
    Fill(i * 2 + 1, next_to_fill);
    nodes_[i].key = *next_to_fill;
    nodes_[i].count = 0;
    (*next_to_fill)++;
    Fill(i * 2 + 2, next_to_fill);
  }

  vector<TreeNode> nodes_;
};

class Solution {
 public:
  vector<int> ComputeLeftLarger(const vector<int>& a) {
    const int n = a.size();

    BinarySearchTree tree(n);

    vector<int> left_larger(n);
    for (int i = 0; i < n; i++) {
      left_larger[i] = tree.NumLargerThan(a[i]);
      tree.Insert(a[i]);
    }
    return left_larger;
  }

 private:
};

int main() {
  ifstream fin("haircut.in");
  int n;
  fin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
  }

  Solution s;
  vector<int> left_larger = s.ComputeLeftLarger(a);

  vector<long long> decrease_by(n + 1);
  for (int i = 0; i < n; i++) {
    decrease_by[a[i]] += left_larger[i];
  }
  ofstream fout("haircut.out");
  long long num_inverse_pairs = 0;
  for (int j = 0; j < n; j++) {
    fout << num_inverse_pairs << endl;
    num_inverse_pairs += decrease_by[j];
  }

  return 0;
}