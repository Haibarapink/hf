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

using vv = vector<int>;
class Solution {
public:
  map<int, int> mp;

  TreeNode *build(vv &preorder, vv &inorder, int pre_l, int pre_r, int in_l,
                  int in_r) {
    if (pre_l > pre_r || in_l > in_r) {
      return nullptr;
    }
    cout << pre_l << " " << pre_r << " " << in_l << " " << in_r << endl;
    int root_val = preorder[pre_l];
    int root_inorder_idx = mp[root_val];

    TreeNode *root = new TreeNode{root_val};
    int left_cnt = root_inorder_idx - in_l;

    root->left = build(preorder, inorder, pre_l + 1, pre_l + left_cnt, in_l,
                       root_inorder_idx - 1);
    root->right = build(preorder, inorder, pre_l + left_cnt + 1, pre_r,
                        root_inorder_idx + 1, in_r);

    return root;
  }

  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    for (auto i = 0; i < preorder.size(); ++i) {
      for (auto j = 0; j < inorder.size(); ++j) {
        if (preorder[i] == inorder[j]) {
          mp[preorder[i]] = j;
          break;
        }
      }
    }
    return build(preorder, inorder, 0, preorder.size() - 1, 0,
                 inorder.size() - 1);
  }
};