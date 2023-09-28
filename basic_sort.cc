#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void basic_sort(vector<string> &nums) {
  vector<vector<string>> slots(10, vector<string>());
  int max_level = 0;
  for (const auto &i : nums) {
    max_level = max(max_level, (int)nums.size());
  }

  for (auto cur_level = 0; cur_level < max_level; ++cur_level) {
    for (auto &num : nums) {
      auto slot = cur_level >= num.size() ? 0 : num[cur_level] - '0';
      slots[slot].push_back(num);
    }

    int p = 0;
    for (auto &slot : slots) {
      for (auto &num : slot) {
        nums[p++] = num;
      }
    }

    for (auto &slot : slots)
      slot.clear();
  }
}

void basic_test() {
  vector<string> nums = {"123", "11111", "1", "12314", "9", "2578"};
  basic_sort(nums);
  cout << nums.size() << " ";
  for (auto i : nums)
    cout << i << " ";
  cout << endl;
}

int main(int, char **) { basic_test(); }