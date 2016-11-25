#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

uint64_t n, m, k;

uint64_t LeftShift(uint64_t a, int shift_amount) {
  for (int i = 0; i < shift_amount; ++i) {
    a = (a + a) % m;
  }
  return a;
}

uint64_t Multiply(uint64_t a, uint64_t b) {
  uint64_t al = a % (1ULL << 32);
  uint64_t ah = a / (1ULL << 32);
  uint64_t bl = b % (1ULL << 32);
  uint64_t bh = b / (1ULL << 32);

  uint64_t result = (LeftShift(ah * bh % m, 64) +
                     LeftShift((ah * bl % m + al * bh % m) % m, 32)) %
                    m;
  result = (result + al * bl % m) % m;
  return result;
}

// g(n) means, allowing leading zeros, the number of valid n-digit numbers.
//   g(0) = 1
//   g(1) = k
//   g(n) = (k-1)(g(n-1) + g(n-2))
//
// f(n) means, not allowing leading zeros, the number of valid n-digit numbers.
//   f(n) = g(n-1)
int main() {
  cin >> n >> k >> m;
  uint64_t a[2][2] = {{0, 1}, {k - 1, k - 1}};
  uint64_t n1 = n - 1;
  vector<int> bits_of_n1;
  while (n1 > 0) {
    bits_of_n1.push_back(n1 % 2);
    n1 /= 2;
  }

  uint64_t b[2][2] = {{1, 0}, {0, 1}};
  while (!bits_of_n1.empty()) {
    uint64_t c[2][2];
    for (int x = 0; x < 2; ++x) {
      for (int y = 0; y < 2; ++y) {
        c[x][y] = 0;
        for (int z = 0; z < 2; ++z) {
          c[x][y] = (c[x][y] + Multiply(b[x][z], b[z][y])) % m;
        }
      }
    }
    int bit = bits_of_n1.back();
    bits_of_n1.pop_back();
    if (bit == 0) {
      memcpy(b, c, sizeof(b));
    } else {
      for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
          b[x][y] = 0;
          for (int z = 0; z < 2; ++z) {
            b[x][y] = (b[x][y] + Multiply(c[x][z], a[z][y])) % m;
          }
        }
      }
    }
  }

  cout << Multiply(k - 1, (b[0][0] + Multiply(b[0][1], k)) % m) << endl;
  return 0;
}
