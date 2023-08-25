class Solution {
public:
  bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
    if (pushed.size() != popped.size())
      return false;
    vector<int> stk;
    int p = 0;
    for (auto i : pushed) {
      stk.push_back(i);
      while (stk.size() && stk.back() == popped[p]) {
        stk.pop_back();
        p++;
      }
    }

    for (; p < popped.size(); ++p) {
      if (stk.back() == popped[p]) {
        stk.pop_back();
      } else {
        return false;
      }
    }
    return stk.empty();
  }
};