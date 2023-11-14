class MinStack {
public:
  vector<int> stack;
  vector<int> min_nums;

  MinStack() {}

  void push(int val) {
    stack.push_back(val);
    if (min_nums.empty()) {
      min_nums.push_back(val);
      return;
    }
    auto cur_min = getMin();
    if (val < getMin()) {
      min_nums.push_back(val);
    } else {
      min_nums.push_back(cur_min);
    }
  }

  void pop() {
    stack.pop_back();
    min_nums.pop_back();
  }

  int top() {
    int tp = stack.back();
    return tp;
  }

  int getMin() { return min_nums.back(); }
};
