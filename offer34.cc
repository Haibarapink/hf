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
  void dfs(TreeNode *cur, vector<int> &vals, int sum, int target,
           bool is_leaf) {
    if (!cur) {
      if (sum == target && is_leaf)
        res.emplace_back(vals);
      return;
    }

    vals.push_back(cur->val);
    is_leaf = !cur->left && !cur->right;
    dfs(cur->left, vals, sum + cur->val, target, is_leaf);
    if (!is_leaf) {
      dfs(cur->right, vals, sum + cur->val, target, is_leaf);
    }
    vals.pop_back();
  }

  vector<vector<int>> pathSum(TreeNode *root, int target) {
    if (!root) {
      return {};
    }
    vector<int> vals;
    dfs(root, vals, 0, target, !root->left && !root->right);
    return res;
  }
};