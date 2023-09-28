#include <iostream>
#include <vector>

using namespace std;
// 快排原理很简单 保证 1...n-1 小于 n处的值  n+1...n大于n处的值即可。
void quick_sort(vector<int> &nums, int start, int end) {
  if (start >= end)
    return;

  int m = nums[start];
  int p = start;
  for (auto i = start + 1; i < end; ++i) {
    if (nums[i] < m) {
      std::swap(nums[i], nums[++p]);
    }
  }
  std::swap(nums[start], nums[p]);
  quick_sort(nums, start, p - 1);
  quick_sort(nums, p + 1, end);
}

void quick_sort() {
  vector<int> nums = {1, 2, 234, 123, 5464, 123, 1, 2, 3, 9, 234, 10};
  quick_sort(nums, 0, nums.size());
  for (auto i : nums)
    cout << i << " ";
  cout << endl;
}

int main(int, char **) { quick_sort(); }