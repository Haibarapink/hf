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
  int high(TreeNode *r) {
    if (!r)
      return 0;
    int l = high(r->left);
    int rgt = high(r->right);
    return max(rgt, l) + 1;
  }

  bool isBalanced(TreeNode *root) {
    if (!root)
      return true;
    bool ok = isBalanced(root->left);
    if (!ok)
      return false;
    ok = isBalanced(root->right);
    if (!ok)
      return false;
    int l = high(root->left);
    int r = high(root->right);
    return abs(l - r) <= 1;
  }
};