class MaxQueue {
public:
  MaxQueue() {}

  // q : 1111111 2
  // a:  1111111 2
  // 维护 a 为单调递减队列
  // q: 1 2 1111
  // a: 1 2
  int max_value() {
    if (q.empty())
      return -1;
    return a.front();
  }

  void push_back(int value) {
    while (a.size() && a.back() < value) {
      a.pop_back();
    }
    a.push_back(value);
    q.push_back(value);
  }

  int pop_front() {
    if (q.empty())
      return -1;
    int fnt = q.front();
    q.pop_front();
    if (a.front() == fnt)
      a.pop_front();
    return fnt;
  }

private:
  list<int> a;
  list<int> q;
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */