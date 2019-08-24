#include <cassert>
#include <cstdio>
#include <map>
#include <queue>

using namespace std;

constexpr int r = 2;
constexpr int c = 4;
constexpr int n = r * c;

int power_of_tens[n];

bool ReadBoard(int* b) {
  if (scanf("%d", b) == EOF) {
    return false;
  }
  for (int i = 1; i < n; ++i) {
    int digit;
    scanf("%d", &digit);
    *b += digit * power_of_tens[i];
  }
  return true;
}

int DigitAtIndex(int number, int i) { return number / power_of_tens[i] % 10; }

int FindZero(int b) {
  for (int i = 0; i < n; ++i) {
    if (DigitAtIndex(b, i) == 0) {
      return i;
    }
  }
  return -1;
}

int Swap(int b, int zero_pos, int neighbor_pos) {
  return b + DigitAtIndex(b, neighbor_pos) *
                 (power_of_tens[zero_pos] - power_of_tens[neighbor_pos]);
}

map<int, int> BFS(int start) {
  map<int, int> step;
  queue<int> q;

  q.push(start);
  step[start] = 0;
  while (!q.empty()) {
    int b = q.front();
    q.pop();

    int zero_pos = FindZero(b);
    assert(zero_pos >= 0);
    int x = zero_pos / c;
    int y = zero_pos % c;

    int neighbors[4];
    int num_neighbors = 0;
    if (x > 0) {
      neighbors[num_neighbors++] = Swap(b, zero_pos, zero_pos - c);
    }
    if (x + 1 < r) {
      neighbors[num_neighbors++] = Swap(b, zero_pos, zero_pos + c);
    }
    if (y > 0) {
      neighbors[num_neighbors++] = Swap(b, zero_pos, zero_pos - 1);
    }
    if (y + 1 < c) {
      neighbors[num_neighbors++] = Swap(b, zero_pos, zero_pos + 1);
    }
    for (int i = 0; i < num_neighbors; ++i) {
      int neighbor = neighbors[i];
      if (!step.count(neighbor)) {
        q.push(neighbor);
        step[neighbor] = step.at(b) + 1;
      }
    }
  }

  return step;
}

int main() {
  power_of_tens[0] = 1;
  for (int i = 1; i < n; ++i) {
    power_of_tens[i] = power_of_tens[i - 1] * 10;
  }

  map<int, int> step = BFS(76543210);

  int b;
  while (ReadBoard(&b)) {
    assert(step.count(b));
    printf("%d\n", step.at(b));
  }
}
