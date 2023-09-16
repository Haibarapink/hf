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
  vector<int> levelOrder(TreeNode *root) {
    if (!root)
      return {};
    queue<TreeNode *> q;
    q.push(root);
    vector<int> res;
    while (q.size()) {
      auto cur = q.front();
      q.pop();
      res.push_back(cur->val);
      if (cur->left)
        q.push(cur->left);
      if (cur->right)
        q.push(cur->right);
    }
    return res;
  }
};