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
  int r{INT_MAX};

  void do_it(TreeNode *n, int dp) {
    if (!n)
      return;
    dp++;
    if (!n->left && !n->right) {
      r = min(dp, r);
    }
    do_it(n->left, dp);
    do_it(n->right, dp);
  }

  int minDepth(TreeNode *root) {
    do_it(root, 0);
    return r;
  }
};