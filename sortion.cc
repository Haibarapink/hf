#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

template <typename T> void print_ln(const T &t) {}

template <> void print_ln<vector<int>>(const vector<int> &v) {
  for (auto i : v) {
    cout << i << " ";
  }
  cout << endl;
}

#define CHECK(expr, a, b)                                                      \
  if (!(expr)) {                                                               \
    print_ln(a);                                                               \
    print_ln(b);                                                               \
    assert(false);                                                             \
  }

// sortion : specific operator of 'operator() (vector<int>& data)'

template <typename Sortion> void check_ok(std::string name) {
  vector<int> data;
  for (auto i = 0; i < 1024; ++i) {
    data.push_back(rand());
  }

  auto copy_data = data;
  sort(copy_data.begin(), copy_data.end());
  Sortion{}(data);
  CHECK(copy_data == data, data, copy_data);

  cout << "pass " + name << endl;
}

struct insert_sortion {
  void operator()(vector<int> &data) {
    size_t n = data.size();
    for (auto sorted = 1; sorted < n; ++sorted) {
      int cur = data[sorted];
      size_t cur_p = 0;
      for (; cur_p < sorted; ++cur_p) {
        if (data[cur_p] >= cur) {
          break;
        }
      }

      // move
      for (auto i = sorted; i > cur_p; --i) {
        data[i] = data[i - 1];
      }

      // insert
      data[cur_p] = cur;
    }
  }
};

int main(int, char **) { check_ok<insert_sortion>("insert_sortion"); }
