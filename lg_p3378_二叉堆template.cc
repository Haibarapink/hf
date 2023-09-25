#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

using namespace std;

class min_pq {
public:
  void push(int n) {
    nums[p] = n;
    swim(p);
    p++;
  }

  int pop() {
    if (p == 0)
      throw std::out_of_range{"sb"};
    int res = nums[0];
    nums[0] = nums[--p];
    shink(0);
    return res;
  }

  // hint: 完全二叉树的中某一节点的左节点
  void shink(int cur) {
    if (cur >= p)
      return;
    // get lft children
    int lft = cur * 2 + 1;
    if (lft < p) {
      if (lft + 1 < p && nums[lft] > nums[lft + 1]) {
        lft++;
      }
      swap(nums[cur], nums[lft]);
      shink(lft);
    }
  }

  // hint: 完全二叉树的父亲节点
  void swim(int cur) {
    int k = cur;
    // find it's parent
    int parent = (cur - 1) / 2; // 向下取整即可
    while (cur != 0 && nums[parent] > nums[cur]) {
      swap(nums[parent], nums[cur]);
      cur = parent;
      parent = cur / 2;
    }
  }

  int p = 0;
  int nums[10000];
};

void test_swim() {
  vector<int> nums = {9, 1, 3, 2, 4, 6, 5, 7, 8};
  min_pq pq;
  for (auto i : nums) {
    pq.push(i);
  }
  for (int i = 0; i < pq.p; ++i) {
    cout << pq.nums[i] << endl;
  }
  cout << "===============================" << endl;
  while (pq.p) {
    cout << pq.pop() << endl;
  }
}

int main() { test_swim(); }