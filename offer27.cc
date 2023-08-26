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
  TreeNode *solution(TreeNode *root) {
    if (!root)
      return nullptr;
    TreeNode *tmp = root;
    auto left = root->left;
    auto right = root->right;
    tmp->left = solution(right);
    tmp->right = solution(left);
    return tmp;
  }

  TreeNode *mirrorTree(TreeNode *root) { return solution(root); }
};