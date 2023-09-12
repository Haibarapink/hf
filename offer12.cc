class Solution {
public:
  using vv = vector<vector<char>>;
  using vis_vv = vector<vector<bool>>;

  bool backstack(const vv &grid, vis_vv &visited, const string &s, int x, int y,
                 int p) {
    int m = grid.size();
    int n = grid[0].size();
    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y]) {
      return false;
    }
    if (s[p] == grid[x][y]) {
      if (p == s.size() - 1) {
        return true;
      }
      visited[x][y] = true;
      bool ok1 = backstack(grid, visited, s, x + 1, y, p + 1);
      bool ok2 = backstack(grid, visited, s, x, y + 1, p + 1);
      bool ok3 = backstack(grid, visited, s, x - 1, y, p + 1);
      bool ok4 = backstack(grid, visited, s, x, y - 1, p + 1);
      visited[x][y] = false;
      if (ok1 || ok2 || ok3 || ok4)
        return true;
    }

    return false;
  }

  bool exist(vector<vector<char>> &board, string word) {
    vis_vv vv = vis_vv(board.size(), vector<bool>(board[0].size(), false));
    for (auto i = 0; i < board.size(); ++i) {
      for (auto j = 0; j < board[0].size(); ++j) {
        bool ok = backstack(board, vv, word, i, j, 0);
        if (ok)
          return ok;
      }
    }
    return false;
  }
};
