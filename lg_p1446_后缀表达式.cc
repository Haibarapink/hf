#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// l expr r
int handle_expr(int l, int r, char expr) {
  switch (expr) {
  case '+':
    return l + r;
  case '-':
    return l - r;
  case '/':
    return l / r;
  case '*':
    return l * r;
  default:
    assert(false);
  }
  // unreachable!
  return -1;
}

int main(int, char **) {
  string data;
  cin >> data;
  int p_num{};
  char p_expr;
  vector<int> stk;
  for (auto ch : data) {
    switch (ch) {
    case '.':
      stk.push_back(p_num);
      p_num = 0;
      break;
    case '0' ... '9':
      p_num = p_num * 10 + ch - '0';
      break;
    case '@':
      break;
    default:
      // expr
      int r = stk.back();
      stk.pop_back();
      int l = stk.back();
      stk.pop_back();
      //   cout << l << " " << ch << " " << r << endl;
      stk.push_back(handle_expr(l, r, ch));
    }
  }
  cout << stk.back() << endl;
  return 0;
}