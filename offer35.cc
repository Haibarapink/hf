/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
  Node *copyRandomList(Node *head) {
    if (head == nullptr)
      return nullptr;
    std::unordered_map<Node *, Node *> src_ref_to_dst;
    Node *new_nodes = new Node{head->val};
    auto runner = new_nodes;
    auto n_head = head;
    src_ref_to_dst.emplace(head, new_nodes);
    head = head->next;
    while (head) {
      int val = head->val;
      runner->next = new Node{val};
      runner = runner->next;
      src_ref_to_dst.emplace(head, runner);
      head = head->next;
    }

    runner = new_nodes;
    // copy random ptr
    while (n_head) {
      auto cor = src_ref_to_dst[n_head->random];
      runner->random = cor;
      runner = runner->next;
      n_head = n_head->next;
    }

    return new_nodes;
  }
};