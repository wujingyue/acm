#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <vector>

struct Station {
  float pos;
  float price;

  bool operator<(const Station& other) const {
    return pos < other.pos;
  }
};

struct Gas {
  float price;
  float amount;
};

int main() {
  float distance;
  float capacity;
  float distance_per_liter;
  float start_price;
  int n;
  std::cin >> distance >> capacity >> distance_per_liter >> start_price >> n;

  n++;
  std::vector<Station> stations(n);
  for (int i = 0; i < n - 1; i++) {
    std::cin >> stations[i].pos >> stations[i].price;
  }
  stations[n - 1].pos = distance;
  stations[n - 1].price = 0.0f;
  std::sort(stations.begin(), stations.end());

  float cost = 0.0f;
  std::deque<Gas> gases;
  gases.push_back(Gas{start_price, capacity});

  float prev_pos = 0.0f;
  for (int i = 0; i < n; i++) {
    float amount_needed = (stations[i].pos - prev_pos) / distance_per_liter;
    while (!gases.empty() && amount_needed > 0.0f) {
      Gas gas = gases.front();
      gases.pop_front();
      float amount_to_use = std::min(gas.amount, amount_needed);
      cost += gas.price * amount_to_use;
      gas.amount -= amount_to_use;
      amount_needed -= amount_to_use;
      if (gas.amount > 0.0f) {
        gases.push_front(gas);
      }
    }
    if (amount_needed > 0.0f) {
      std::cout << "No Solution" << std::endl;
      return 0;
    }

    float amount_to_add = (stations[i].pos - prev_pos) / distance_per_liter;
    while (!gases.empty() && gases.back().price >= stations[i].price) {
      amount_to_add += gases.back().amount;
      gases.pop_back();
    }
    gases.push_back(Gas{stations[i].price, amount_to_add});

    prev_pos = stations[i].pos;
  }

  std::cout << std::fixed << std::setprecision(2) << cost << std::endl;
  return 0;
}
