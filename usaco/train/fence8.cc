/*
ID: koalawj1
PROG: fence8
LANG: C++11
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

constexpr int kMaxNumBoards = 64;
constexpr int kMaxNumRails = 1024;

int boards[kMaxNumBoards];
int rails[kMaxNumRails];
int sum_rails[kMaxNumRails];
int num_boards;
int num_rails;

bool Possible(int rail_id, int sum_boards, int last_board_id) {
  if (rail_id < 0) {
    return true;
  }

  if (sum_rails[rail_id] > sum_boards) {
    return false;
  }

  int start_board_id = 0;
  // If this rail has the same length as last rail, try a board ID >= last board
  // ID.
  if (rail_id + 1 < num_rails && rails[rail_id] == rails[rail_id + 1] &&
      last_board_id >= 0) {
    start_board_id = last_board_id;
  }
  for (int i = start_board_id; i < num_boards; ++i) {
    if (boards[i] == rails[rail_id]) {
      boards[i] = 0;
      bool possible = Possible(rail_id - 1, sum_boards - rails[rail_id], i);
      boards[i] = rails[rail_id];
      return possible;
    }
  }

  for (int i = start_board_id; i < num_boards; ++i) {
    if (boards[i] > rails[rail_id]) {
      boards[i] -= rails[rail_id];
      int next_sum_boards = sum_boards - rails[rail_id];
      if (boards[i] < rails[0]) {
        next_sum_boards -= boards[i];
      }
      bool possible = Possible(rail_id - 1, next_sum_boards, i);
      boards[i] += rails[rail_id];
      if (possible) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  ifstream fin("fence8.in");
  ofstream fout("fence8.out");
  fin >> num_boards;
  for (int i = 0; i < num_boards; ++i) {
    fin >> boards[i];
  }
  sort(boards, boards + num_boards);
  fin >> num_rails;
  for (int i = 0; i < num_rails; ++i) {
    fin >> rails[i];
  }
  sort(rails, rails + num_rails);
  memset(sum_rails, 0, sizeof(sum_rails));
  sum_rails[0] = rails[0];
  for (int i = 1; i < num_rails; ++i) {
    sum_rails[i] = sum_rails[i - 1] + rails[i];
  }

  int sum_boards = accumulate(boards, boards + num_boards, 0, std::plus<int>());
  int num_cut_rails = 1;
  while (num_cut_rails <= num_rails &&
         Possible(num_cut_rails - 1, sum_boards, -1)) {
    ++num_cut_rails;
  }
  fout << num_cut_rails - 1 << endl;

  return 0;
}
