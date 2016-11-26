#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class BigNumber {
 public:
  BigNumber(vector<int>::const_iterator begin, vector<int>::const_iterator end)
      : digits_(begin, end) {
    reverse(digits_.begin(), digits_.end());
    assert(digits_.back() > 0);
  }

  vector<int>::reverse_iterator begin() { return digits_.rbegin(); }
  vector<int>::reverse_iterator end() { return digits_.rend(); }
  int size() const { return digits_.size(); }
  int& operator[](int i) { return digits_[i]; }
  int operator[](int i) const { return digits_[i]; }

  static BigNumber MaxLimit() {
    vector<int> digits(10000, 9);
    return BigNumber(digits.begin(), digits.end());
  }

  void Normalize() {
    for (int i = 0; i < digits_.size(); ++i) {
      if (digits_[i] > 9) {
        if (i + 1 >= digits_.size()) {
          digits_.push_back(0);
        }
        digits_[i + 1] += digits_[i] / 10;
        digits_[i] %= 10;
      } else {
        while (digits_[i] < 0) {
          digits_[i] += 10;
          assert(i + 1 < digits_.size());
          --digits_[i + 1];
        }
      }
    }
    while (digits_.size() > 0 && digits_.back() == 0) {
      digits_.pop_back();
    }
  }

  void Increase(int delta) {
    if (digits_.empty()) {
      digits_.push_back(delta);
    } else {
      digits_[0] += delta;
    }
    Normalize();
  }

  void Multiply(int multiplier) {
    for (int i = 0; i < digits_.size(); ++i) {
      digits_[i] *= multiplier;
    }
    Normalize();
  }

  void Minimum(const BigNumber& b) {
    if (b.digits_.size() < digits_.size()) {
      *this = b;
      return;
    }
    if (b.digits_.size() > digits_.size()) {
      return;
    }

    for (int i = (int)digits_.size() - 1; i >= 0; --i) {
      if (b.digits_[i] < digits_[i]) {
        *this = b;
        return;
      }
      if (b.digits_[i] > digits_[i]) {
        return;
      }
    }
  }

  string ToString() const {
    assert(digits_.size() > 0);
    string result;
    for (auto i = digits_.rbegin(); i != digits_.rend(); ++i) {
      result += '0' + *i;
    }
    return result;
  }

 private:
  vector<int> digits_;
};

ostream& operator<<(ostream& os, const BigNumber& big_number) {
  os << big_number.ToString();
  return os;
}

vector<int> a;
int n;

template<typename Iter0, typename Iter1>
bool Match(Iter0 begin0, Iter0 end0, Iter1 begin1, Iter1 end1) {
  while (begin0 != end0 && begin1 != end1 && *begin0 == *begin1) {
    ++begin0;
    ++begin1;
  }
  return begin0 == end0 || begin1 == end1;
}

bool MatchForward(int start, int end) {
  BigNumber pattern(a.begin() + start, a.begin() + end);
  int pos = end;
  while (pos < n) {
    pattern.Increase(1);
    if (Match(pattern.begin(), pattern.end(), a.begin() + pos, a.end())) {
      pos += pattern.size();
    } else {
      return false;
    }
  }
  return true;
}

bool MatchBackward(int start, int end) {
  BigNumber pattern(a.begin() + start, a.begin() + end);
  int pos = start;
  while (pos > 0) {
    pattern.Increase(-1);
    if (pattern.size() == 0) {
      // Series starts from 1.
      return false;
    }
    pos -= (int)pattern.size();
    if (pos >= 0) {
      if (!Match(pattern.begin(), pattern.end(), a.begin() + pos, a.end())) {
        return false;
      }
    } else {
      if (!Match(pattern.begin() + (-pos), pattern.end(), a.begin(), a.end())) {
        return false;
      }
    }
  }
  return true;
}

BigNumber DigitsBefore(const BigNumber &a) {
  BigNumber digits_before = a;
  digits_before.Multiply(a.size());
  for (int i = 0; i < a.size(); ++i) {
    --digits_before[i];
  }
  digits_before.Normalize();
  return digits_before;
}

void UpdateWindowStartPosition(const BigNumber& pattern,
                               int pattern_start_pos_in_window,
                               BigNumber* min_window_start_pos) {
  BigNumber window_start_pos = DigitsBefore(pattern);
  window_start_pos.Increase(-pattern_start_pos_in_window);
  window_start_pos.Increase(1);
  min_window_start_pos->Minimum(window_start_pos);
}

int main() {
  string s;
  cin >> s;
  n = s.length();
  for (int i = 0; i < n; ++i) {
    a.push_back(s[i] - '0');
  }

  BigNumber min_window_start_pos = BigNumber::MaxLimit();
  // whole number
  for (int start = 0; start < n; ++start) {
    if (a[start] == 0) {
      continue;
    }
    for (int end = start + 1; end <= n; ++end) {
      if (MatchForward(start, end) && MatchBackward(start, end)) {
        UpdateWindowStartPosition(BigNumber(a.begin() + start, a.begin() + end),
                                  start, &min_window_start_pos);
      }
    }
  }

  // partial number
  for (int split = 1; split < n; ++split) {
    if (a[split] == 0)
      continue;
    vector<int> left_suffix(a.begin(), a.begin() + split);
    left_suffix.insert(left_suffix.begin(), 1);  // bogus digit
    BigNumber pattern(left_suffix.begin(), left_suffix.end());
    pattern.Increase(1);
    auto pattern_start = pattern.begin() + 1;
    // left_suffix_start + split > n otherwise whole number
    // left_suffix_start > n - split
    // left_suffix_start >= n - split + 1
    for (int left_suffix_start = max(split + 1, n - split + 1);
         left_suffix_start <= n; ++left_suffix_start) {
      if (Match(pattern_start, pattern.end(), a.begin() + left_suffix_start,
                a.end())) {
        vector<int> right_number(a.begin() + split, a.begin() + left_suffix_start);
        copy(pattern_start, pattern.end(), back_inserter(right_number));
        UpdateWindowStartPosition(
            BigNumber(right_number.begin(), right_number.end()), split,
            &min_window_start_pos);
      }
    }
  }

  {
    vector<int> digits = a;
    digits.insert(digits.begin(), 1);
    UpdateWindowStartPosition(BigNumber(digits.begin(), digits.end()), -1,
                              &min_window_start_pos);
  }

  cout << min_window_start_pos << endl;
  return 0;
}
