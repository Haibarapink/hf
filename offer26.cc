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
  bool cmp_dfs(TreeNode *l, TreeNode *r, bool is_connected = false) {
    if (r == nullptr) {
      return true;
    }
    if (l == nullptr && r) {
      return false;
    }
    if (r->val == l->val) {
      bool lft_ok = cmp_dfs(l->left, r->left, true);
      bool rit_ok = cmp_dfs(l->right, r->right, true);
      if (lft_ok && rit_ok) {
        return true;
      }
    }

    if (is_connected)
      return false;

    bool l_ok = cmp_dfs(l->left, r);
    bool r_ok = cmp_dfs(l->right, r);
    return l_ok || r_ok;
  }

  bool isSubStructure(TreeNode *A, TreeNode *B) {
    if (!A || !B)
      return false;
    return cmp_dfs(A, B);
  }
};