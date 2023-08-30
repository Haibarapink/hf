class Solution {
public:
  template <typename RandomIterator>
  RandomIterator skip_blank_space(RandomIterator iter, RandomIterator end) {
    while (iter != end && *iter == ' ') {
      iter++;
    }
    return iter;
  }

  template <typename RandomIterator> bool is_valid(RandomIterator iter) {
    char ch = *iter;
    return (ch >= '0' && ch <= '9');
  }

  int strToInt(string str) {
    long res = 0;
    bool greater_than_zero = true;
    auto iter = skip_blank_space(str.begin(), str.end());
    // check symbol
    if (iter == str.end())
      return 0;
    if (*iter == '-' || *iter == '+') {
      if (*iter == '-')
        greater_than_zero = false;
      iter++;
    }
    while (iter != str.end() && is_valid(iter)) {
      res = res * 10 + *iter - '0';
      if (res > INT_MAX) {
        return greater_than_zero ? INT_MAX : INT_MIN;
      }
      iter++;
    }
    return greater_than_zero ? (int)res : (int)-res;
  }
};