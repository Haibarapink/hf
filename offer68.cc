/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  bool look_up(TreeNode *cur, TreeNode *p) {
    if (!cur)
      return false;
    if (cur == p)
      return true;
    return look_up(cur->left, p) || look_up(cur->right, p);
  }

  TreeNode *near_anc(TreeNode *root, TreeNode *p, TreeNode *q) {
    bool is_anc = look_up(root, p) && look_up(root, q);
    if (!is_anc)
      return nullptr;

    // check children
    auto lft = near_anc(root->left, p, q);
    if (lft) {
      return lft;
    }
    auto rft = near_anc(root->right, p, q);
    if (rft) {
      return rft;
    }

    return root;
  }

  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (q == p)
      return p;
    if (!q || !p)
      return nullptr;
    return near_anc(root, p, q);
  }
};