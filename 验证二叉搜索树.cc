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
  void hold(TreeNode *root, vector<int> &datas) {
    if (!root)
      return;
    hold(root->left, datas);
    datas.push_back(root->val);
    hold(root->right, datas);
  }

  bool isValidBST(TreeNode *root) {
    if (!root)
      return true;
    vector<int> datas;
    hold(root, datas);
    for (auto i = 1; i < datas.size(); ++i) {
      if (datas[i - 1] >= datas[i])
        return false;
    }
    return true;
  }
};