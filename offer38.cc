class Solution {
public:
  set<string> set;
  void backstack(const string &s, string &ans, vector<bool> &used, int used_cnt,
                 vector<string> &res) {
    if (used_cnt == s.size()) {
      if (set.count(ans) > 0)
        return;
      set.insert(ans);
      res.push_back(ans);
      return;
    }
    for (int i = 0; i < s.size(); ++i) {
      if (used[i] == 1)
        continue;
      used[i] = 1;
      ans.push_back(s[i]);
      backstack(s, ans, used, used_cnt + 1, res);

      // after that shit
      used[i] = 0;
      ans.pop_back();
    }
  }

  vector<string> permutation(string s) {
    vector<string> res;
    string ans;
    vector<bool> used(s.size(), 0);
    backstack(s, ans, used, 0, res);
    return res;
  }
};