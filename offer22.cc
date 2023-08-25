/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  ListNode *getKthFromEnd(ListNode *head, int k) {
    ListNode *tail = head, *cur = head;
    for (auto i = 0; i < k; ++i) {
      if (!tail)
        return nullptr;
      tail = tail->next;
    }
    while (tail) {
      tail = tail->next;
      cur = cur->next;
    }
    return cur;
  }
};