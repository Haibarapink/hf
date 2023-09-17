/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
  Node *split(Node *n, bool is_left = true) {
    if (n == nullptr)
      return nullptr;
    auto lft = split(n->left);
    auto rft = split(n->right, false);
    // 设置链表
    if (lft) {
      lft->right = n;
      n->left = lft;
    }
    if (rft) {
      rft->left = n;
      n->right = rft;
    }
    if (is_left) {
      // 这里式最侧的部分， 返回最右边的节点
      while (n->right) {
        n = n->right;
      }
    } else {
      while (n->left) {
        n = n->left;
      }
    }
    return n;
  }

  Node *treeToDoublyList(Node *root) {
    if (!root)
      return nullptr;
    auto res = split(root);
    // find tail
    auto tail = res;
    auto head = res;
    while (tail->right) {
      cout << tail->val << endl;
      tail = tail->right;
    }
    while (head->left) {
      head = head->left;
    }
    head->left = tail;
    tail->right = head;
    return head;
  }
};