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
  map<int, int> mmp;

public:
  TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int p_left,
                       int p_right, int in_left, int in_right) {
    if (p_left > p_right || in_left > in_right)
      return nullptr;
    // root;
    int root_val = postorder[p_right];
    int root_inorder_p = mmp[root_val];

    // left node count
    int left_cnt = root_inorder_p - in_left;
    int div = p_left + left_cnt - 1;

    TreeNode *root = new TreeNode{root_val};
    root->left = _buildTree(inorder, postorder, p_left, div, in_left,
                            root_inorder_p - 1);
    root->right = _buildTree(inorder, postorder, div + 1, p_right - 1,
                             root_inorder_p + 1, in_right);
    return root;
  }

  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    for (auto i : postorder) {
      for (auto j = 0; j < inorder.size(); ++j) {
        if (i == inorder[j]) {
          mmp[i] = j;
          break;
        }
      }
    }

    return _buildTree(inorder, postorder, 0, postorder.size() - 1, 0,
                      inorder.size() - 1);
  }
};