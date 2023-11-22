#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <iterator>
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

// sortion : revoke specific operator: 'void operator() (vector<int>& data)'

template <typename Sortion> void check_ok(std::string name) {
  vector<int> data;
  for (auto i = 0; i < 16; ++i) {
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

struct select_sortion {
  void operator()(vector<int> &data) {
    size_t n = data.size();
    for (auto sorted = 0; sorted < n; ++sorted) {
      size_t min_in_unsorted = sorted;
      int min_num = data[min_in_unsorted];
      for (auto j = sorted; j < n; ++j) {
        if (min_num > data[j]) {
          min_in_unsorted = j;
          min_num = data[min_in_unsorted];
        }
      }

      swap(data[min_in_unsorted], data[sorted]);
    }
  }
};

struct bubble_sortion {
  void operator()(vector<int> &data) {
    size_t n = data.size();
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n - i - 1; ++j) {
        if (data[j] > data[j + 1]) {
          swap(data[j], data[j + 1]);
        }
      }
    }
  }
};

struct shell_sortion {
  void operator()(vector<int> &data) {
    size_t n = data.size();
    for (auto gap = n / 2; gap > 0; gap /= 2) {
      for (auto i = gap; i < n; ++i) {
        int tmp = data[i];
        for (auto j = i; j >= gap && data[j] < data[j - gap]; j -= gap) {
          swap(data[j], data[j - gap]);
        }
      }
    }
  }
};

// build heap in origin array
struct heap_sortion {
  void operator()(vector<int> &data) {
    size_t n = data.size();
    for (auto heap_len = 1; heap_len < n - 1; ++heap_len) {
      size_t len = heap_len + 1;
      // heap insertion
      while (true) {
        if (data[(len - 1) / 2] > data[len]) {
          swap(data[(len - 1) / 2], data[len]);
        }
        if ((len - 1) / 2 == 0)
          break;
        len = (len - 1) / 2;
      }
    }
  }
};

struct quick_sortion {
  void inner(vector<int> &d, size_t l, size_t r) {
    if (l >= r)
      return;
    int m = d[l];
    int p = l;
    for (auto i = p + 1; i < r; ++i) {
      if (d[i] < m) {
        swap(d[++p], d[i]);
      }
    }
    swap(d[l], d[p]);
    inner(d, l, p);
    inner(d, p + 1, r);
  }

  void operator()(vector<int> &data) {
    size_t n = data.size();
    inner(data, 0, n);
  }
};

int main(int, char **) {
  check_ok<insert_sortion>("insert_sortion");
  check_ok<select_sortion>("select_sortion");
  check_ok<bubble_sortion>("bubble_sortion");
  check_ok<shell_sortion>("shell_sortion");
  check_ok<quick_sortion>("quick_sortion");
  // check_ok<heap_sortion>("heap_sortion"); this is a heap...
  //  todo write check heap
}
