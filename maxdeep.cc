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
  void dfs(TreeNode *root, int cur, int &res) {
    if (!root)
      return;
    res = max(res, cur + 1);
    dfs(root->left, cur + 1, res);
    dfs(root->right, cur + 1, res);
  }

  int maxDepth(TreeNode *root) {
    int res{0};
    dfs(root, 0, res);
    return res;
  }
};