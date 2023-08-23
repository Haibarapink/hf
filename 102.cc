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
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (!root) {
      return {};
    }
    queue<TreeNode *> q;
    q.push(root);

    vector<vector<int>> res;
    size_t level_cnt = 1;
    while (!q.empty()) {
      vector<int> tmp;
      // check level
      size_t next_lvl_cnt = 0;
      for (auto i = 0; i < level_cnt; ++i) {
        auto n = q.front();
        q.pop();
        tmp.push_back(n->val);
        if (n->left) {
          next_lvl_cnt++;
          q.push(n->left);
        }
        if (n->right) {
          next_lvl_cnt++;
          q.push(n->right);
        }
      }
      level_cnt = next_lvl_cnt;

      res.emplace_back(std::move(tmp));
    }

    return res;
  }
};