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
  void hold(vector<TreeNode *> &v, TreeNode *t) {
    if (!t)
      return;
    hold(v, t->left);
    v.push_back(t);
    hold(v, t->right);
  }

  void recoverTree(TreeNode *root) {
    vector<TreeNode *> v;
    hold(v, root);
    int a{-1}, b{-1};
    for (auto i = 1; i < v.size(); ++i) {
      if (v[i - 1]->val > v[i]->val) {
        if (a == -1) {
          a = i - 1;
        } else {
          b = i;
        }
      }
    }

    //
    if (b == -1) {
      b = a + 1;
    }

    std::swap(v[a]->val, v[b]->val);
  }
};