#include <array>
#include <assert.h>
#include <iostream>
#include <optional>
#include <vector>

template <typename T, size_t M> struct node {
  using t_node_ptr = node *;
  using t_node = node<T, M>;

  size_t element_count = 0;
  size_t pointer_count = 0;
  std::array<t_node_ptr, M + 1> children = {nullptr};
  std::array<T, M + 1> element = {}; // 最多存M个元素，多留一个在分裂的时候用。

  // 会返回是否有相等的元素，如果有，p是最后一个相等的元素的位置
  bool binary_search(const T &t, size_t &p) const {
    int l = -1, r = element_count;
    while (l + 1 != r) {
      int mid = (l + r) / 2;
      if (element[mid] > t) {
        r = mid;
      } else {
        l = mid;
      }
    }

    // 全都比t大
    if (l == -1) {
      p = 0;
      return false;
    } else if (p == element_count) {
      p = element_count;
      return false;
    } else {
      p = (size_t)l;
    }

    return t == element[l];
  }
  // p 是应该插入的位置， 第一个比t大的元素
  bool seek_insert_idx(const T &t, size_t &p) const {
    int l = -1, r = element_count;
    while (l + 1 != r) {
      int mid = (l + r) / 2;
      if (element[mid] > t) {
        r = mid;
      } else {
        l = mid;
      }
    }

    // 全都比t大
    if (l == -1) {
      p = 0;
      return false;
    } else if (p == element_count) {
      p = element_count;
      return false;
    } else {
      p = (size_t)r;
    }

    return t == element[l];
  }

  void insert(T t) {
    size_t p = 0;
    bool contain_same = seek_insert_idx(t, p);
    assert(!contain_same && "不应该存在相同的元素");
    size_t element_cnt = element_count;
    for (int i = element_cnt; i > p && i > 0; --i) {
      element[i] = element[i - 1];
    }
    element[p] = std::move(t);
    element_count++;
  }

  bool need_split() const { return element_count > M; }

  // 4 -> 2, 1
  // 5 -> 2, 2
  // ele cnt / 2
  void splite2(t_node &right, T &mid_k) {
    size_t remain = element_count / 2;
    // copy to right node
    size_t cp_i = 0;
    for (auto i = remain + 1; i < element_count; ++i) {
      right.element[cp_i++] = element[i];
    }
    right.element_count = cp_i;
    // copy mid key
    mid_k = element[remain];
    // update *-self
    element_count = remain;
  }

  // 关于更新parent的指针
  // case.1
  // 3-4 (3 elements, 4 pointers)
  //  1 2 3
  // 0 1 2 3
  // k-left = k+1/2
  // k-right = k+1/2 + 1
  void splite3(t_node &right, t_node &parent) {
    T mid;
    splite2(right, mid);
    parent.insert(mid);
    size_t p = 0;
    bool ok = parent.binary_search(mid, p);
    assert(ok && p < parent.element_count && parent.element[p] == mid);
    // update parent's pointer
    size_t lft = (p + 1) / 2;
    size_t rit = lft + 1;
    parent.children[rit] = &right;
    parent.children[lft] = this;
    parent.pointer_count++;
  }
};

// test insertion , looking-up and binary-search
void node_oper_test() {
  std::vector<int> nums = {1, 5, 4, 6, 2, 3, 7, 8, 9};
  node<int, 9> nd;
  for (auto num : nums)
    nd.insert(num);
  for (auto i = 0; i < nums.size(); ++i) {
    size_t p = 0;
    bool ok = nd.seek_insert_idx(nums[i], p);
    // std::cout << "look up " << nums[i] << " " << ok << " " << p << std::endl;
    if (ok) {
      if (p < nd.element_count)
        assert(nd.element[p] > nums[i]);
    } else {
      assert(false);
    }
  }

  // test binary search
  for (auto i = 0; i < nums.size(); ++i) {
    size_t p = 0;
    bool ok = nd.binary_search(nums[i], p);
    // std::cout << "binary search " << nums[i] << " " << ok << " " << p <<
    // std::endl;
    assert(ok && p < nd.element_count && nd.element[p] == nums[i]);
  }
}

// test split2
void splite2_test() {
  std::vector<int> nums = {1, 2, 3, 4, 5};
  node<int, 5> nd;
  for (auto i : nums) {
    nd.insert(i);
  }

  node<int, 5> other;
  int mid = 991234;
  nd.splite2(other, mid);
  assert(other.element_count == 2 && nd.element_count == 2 && mid == 3);
  assert(nd.element[0] == 1 && nd.element[1] == 2);
  assert(other.element[0] == 4 && other.element[1] == 5);
}

void split2_test2() {
  std::vector<int> nums = {1, 2, 3, 4, 5, 6};
  node<int, 5> nd;
  for (auto i : nums) {
    nd.insert(i);
  }

  node<int, 5> other;
  int mid = 991234;
  nd.splite2(other, mid);
  assert(other.element_count == 2 && nd.element_count == 3 && mid == 4);
  assert(nd.element[0] == 1 && nd.element[1] == 2 && nd.element[2] == 3);
  assert(other.element[0] == 5 && other.element[1] == 6);
}

void split3_test() {
  std::vector<int> nums = {1, 2, 3, 4, 5, 6};
  node<int, 5> nd;
  for (auto i : nums) {
    nd.insert(i);
  }

  node<int, 5> other;
  node<int, 5> parent;
  nd.splite3(other, parent);
  std::cout << "parent " << parent.element_count << std::endl;
  assert(other.element_count == 2 && nd.element_count == 3 &&
         parent.element_count == 1);
  assert(nd.element[0] == 1 && nd.element[1] == 2 && nd.element[2] == 3);
  assert(other.element[0] == 5 && other.element[1] == 6);
  assert(parent.element[0] == 4);

  // test parent's pointer
  assert(parent.children[0] == &nd);
  assert(parent.children[1] == &other);
}

int main(int, char **) {
  node_oper_test();
  splite2_test();
  split2_test2();
  split3_test();
}