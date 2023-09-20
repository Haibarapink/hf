#include <iostream>
#include <vector>
using namespace std;

int main(int, char **) {
  int n, m;
  cin >> n >> m;

  vector<int> hums;
  for (auto i = 0; i < n; ++i)
    hums.emplace_back(i);
  m--;
  int cur_p = 0;
  while (n) {
    int skip_cnt = 0;
    while (skip_cnt != m) {
      if (hums[cur_p] != -1) {
        skip_cnt++;
      }
      cur_p++;
      cur_p %= hums.size();
    }
    while (hums[cur_p] == -1) {
      cur_p++;
      cur_p %= hums.size();
    }

    cout << hums[cur_p] + 1 << " ";
    hums[cur_p] = -1;
    n--;
  }

  return 0;
}