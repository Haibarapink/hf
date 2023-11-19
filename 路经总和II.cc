/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  vector<vector<int>> res;

  void dfs(TreeNode *t, int cur, int targetSum, vector<int> &d) {
    if (!t)
      return;
    cur += t->val;
    d.push_back(t->val);
    if (!t->left && !t->right) {
      if (cur == targetSum)
        res.emplace_back(d);
    }
    dfs(t->left, cur, targetSum, d);
    dfs(t->right, cur, targetSum, d);
    d.pop_back();
  }

  vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
    vector<int> d;
    dfs(root, 0, targetSum, d);
    return res;
  }
};