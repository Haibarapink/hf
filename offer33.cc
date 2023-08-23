class Solution {
public:
  // in range
  // end is the index of root in p
  bool verify_in_range(vector<int> &p, int start, int end) {
    if (start >= end)
      return true;
    // look up the first item of p which is smaller than p[end-1]
    int root_item = p[end];
    int left_root = end - 1;

    for (auto i = end - 1; i >= start; --i) {
      left_root = i;
      if (p[i] <= root_item) {
        break;
      }
    }

    // check left and right
    for (auto i = start; i < left_root; ++i) {
      if (p[i] > root_item) {
        return false;
      }
    }
    for (auto i = left_root + 1; i < end - 1; ++i) {
      if (p[i] <= root_item) {
        return false;
      }
    }

    // ok for left range, and p
    bool left_ok = verify_in_range(p, start, left_root);
    // ok for right range
    bool right_ok = verify_in_range(p, left_root + 1, end - 1);
    if (!left_ok || !right_ok)
      return false;
    return true;
  }

  bool verifyPostorder(vector<int> &postorder) {
    return verify_in_range(postorder, 0, postorder.size() - 1);
  }
};