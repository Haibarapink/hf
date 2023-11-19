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
  bool dfs(TreeNode *t, int cur, int targetSum) {
    if (!t)
      return false;
    cur += t->val;
    if (!t->left && !t->right) {
      if (cur != targetSum)
        return false;
      else
        return true;
    }
    bool ok = dfs(t->left, cur, targetSum);
    if (ok)
      return ok;
    ok = dfs(t->right, cur, targetSum);
    if (ok)
      return ok;
    return false;
  }

  bool hasPathSum(TreeNode *root, int targetSum) {
    if (!root)
      return false;
    return dfs(root, 0, targetSum);
  }
};