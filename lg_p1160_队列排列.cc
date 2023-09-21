#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

auto mf = [](list<int>::iterator b, list<int>::iterator end,
             int val) -> list<int>::iterator {
  while (b != end) {
    if (*b == val)
      break;
    b++;
  }
  return b;
};

int main(int, char **) {
  int N;
  cin >> N;
  list<int> guys;
  guys.push_back(1);
  map<int, list<int>::iterator> map;
  map.emplace(1, guys.begin());
  for (auto i = 2; i <= N; ++i) {
    int k, p;
    cin >> k >> p;
    p = p == 0 ? -1 : 1;
    auto pos = map[k];

    assert(pos != guys.end());

    if (p == 1)
      pos++;
    auto iter = guys.insert(pos, i);
    map.emplace(i, iter);
  }
  // M
  int M;
  cin >> M;

  for (auto i = 0; i < M; ++i) {
    int x;
    cin >> x;
    auto iter = map.find(x);
    if (iter != map.end()) {
      guys.erase(iter->second);
      map.erase(iter);
      ;
    }
  }

  for (auto i : guys) {
    cout << i << " ";
  }

  return 0;
}