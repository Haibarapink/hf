class max_pq {
public:
  max_pq(size_t max_size) : max_size_(max_size) {}

  int max() const {
    if (q.empty())
      return INT_MIN;
    return max_cnt.front();
  }

  void push(int val) {
    while (max_cnt.size() && max_cnt.back() < val)
      max_cnt.pop_back();
    max_cnt.push_back(val);
    q.push_back(val);
    if (q.size() > max_size_) {
      assert(false);
      pop_front();
    }
  }

  int pop_front() {
    if (q.empty())
      return INT_MIN;
    int res = q.front();
    if (max_cnt.front() == res)
      max_cnt.pop_front();
    q.pop_front();
    return res;
  }

  size_t size() const { return q.size(); }

private:
  size_t max_size_;
  list<long> q;
  list<long> max_cnt;
};

class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    auto p = max_pq(k);
    vector<int> res;
    for (int i = 0; i < k; ++i) {
      p.push(nums[i]);
    }
    res.push_back(p.max());
    for (auto i = k; i < nums.size(); ++i) {
      if (p.size() == k)
        p.pop_front();
      p.push(nums[i]);
      res.push_back(p.max());
    }

    return res;
  }
};