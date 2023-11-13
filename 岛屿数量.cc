class Solution {
public:
  using vv = vector<vector<char>>;

  void clean(vv &grid, int x, int y) {
    int n = grid.size();
    int m = grid[0].size();
    if (x < 0 || x >= n || y < 0 || y >= m)
      return;
    if (grid[x][y] != '1')
      return;
    grid[x][y] = '0';
    clean(grid, x + 1, y);
    clean(grid, x, y + 1);
    clean(grid, x - 1, y);
    clean(grid, x, y - 1);
  }

  void compute(int &res, vv &grid, int x, int y) {
    int n = grid.size();
    int m = grid[0].size();
    if (x < 0 || x >= n || y < 0 || y >= m)
      return;
    if (grid[x][y] != '1')
      return;
    clean(grid, x, y);
    res++;
  }

  int numIslands(vector<vector<char>> &grid) {
    int res = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        compute(res, grid, i, j);
      }
    }

    return res;
  }
};