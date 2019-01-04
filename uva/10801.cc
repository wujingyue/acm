#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

static const int kNumFloors = 100;
static const int kTimeToSwitch = 60;

struct NodeDistance {
  int floor;
  int elevator;
  int distance;

  NodeDistance() : floor(-1), elevator(-1), distance(INT_MAX) {}
  NodeDistance(int f, int e, int d) : floor(f), elevator(e), distance(d) {}

  bool operator<(const NodeDistance& other) const {
    return distance > other.distance;
  }
};

int Dijkstra(const vector<vector<int> >& elevator_floors,
             const vector<int>& time_to_adjacent, int dest_floor) {
  int num_elevators = elevator_floors.size();
  vector<vector<int> > d(kNumFloors, vector<int>(num_elevators, INT_MAX));
  vector<vector<bool> > dequeued(kNumFloors, vector<bool>(num_elevators));
  priority_queue<NodeDistance> q;

  for (int i = 0; i < num_elevators; ++i) {
    if (binary_search(elevator_floors[i].begin(), elevator_floors[i].end(),
                      0)) {
      q.push(NodeDistance(0, i, 0));
      d[0][i] = 0;
    }
  }

  while (!q.empty()) {
    NodeDistance nd = q.top();
    q.pop();

    int floor = nd.floor;
    int i = nd.elevator;
    if (floor == dest_floor) {
      return nd.distance;
    }

    // The same node may appear mutliple times in the priority queue due to lazy
    // deletion. We only expand the one with the smallest distance.
    if (dequeued[floor][i]) {
      continue;
    }
    dequeued[floor][i] = true;

    NodeDistance neighbors[3];
    int num_neighbors = 0;
    // Switch to another elevator.
    for (int j = 0; j < num_elevators; ++j) {
      if (j == i) {
        continue;
      }

      if (binary_search(elevator_floors[j].begin(), elevator_floors[j].end(),
                        floor)) {
        neighbors[num_neighbors++] =
            NodeDistance(floor, j, nd.distance + kTimeToSwitch);
      }
    }
    // Up.
    int floor_index = lower_bound(elevator_floors[i].begin(),
                                  elevator_floors[i].end(), floor) -
                      elevator_floors[i].begin();
    assert(floor_index < (int)elevator_floors[i].size());
    assert(elevator_floors[i][floor_index] == floor);
    if (floor_index + 1 < (int)elevator_floors[i].size()) {
      int next_floor = elevator_floors[i][floor_index + 1];
      neighbors[num_neighbors++] = NodeDistance(
          next_floor, i,
          nd.distance + time_to_adjacent[i] * (next_floor - floor));
    }
    // Down.
    if (floor_index > 0) {
      int prev_floor = elevator_floors[i][floor_index - 1];
      neighbors[num_neighbors++] = NodeDistance(
          prev_floor, i,
          nd.distance + time_to_adjacent[i] * (floor - prev_floor));
    }

    // Add neighbors to the priority queue.
    for (int k = 0; k < num_neighbors; ++k) {
      const NodeDistance& neighbor = neighbors[k];
      if (neighbor.distance < d[neighbor.floor][neighbor.elevator]) {
        d[neighbor.floor][neighbor.elevator] = neighbor.distance;
        q.push(neighbor);
      }
    }
  }
  return -1;
}

int main() {
  int num_elevators;
  int dest_floor;
  while (cin >> num_elevators >> dest_floor) {
    vector<int> time_to_adjacent(num_elevators);
    for (int i = 0; i < num_elevators; ++i) {
      cin >> time_to_adjacent[i];
    }

    string line;
    getline(cin, line);
    vector<vector<int> > elevator_floors(num_elevators);
    for (int i = 0; i < num_elevators; ++i) {
      getline(cin, line);
      istringstream iss(line);
      int floor;
      while (iss >> floor) {
        elevator_floors[i].push_back(floor);
      }
    }

    int min_dist = Dijkstra(elevator_floors, time_to_adjacent, dest_floor);
    if (min_dist < 0) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << min_dist << endl;
    }
  }
}
