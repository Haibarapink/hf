class Solution {
public:
  void dfs(vector<vector<int>> &visited, int &all, int x, int y, int k) {
    if (x < 0 || x >= visited.size() || y < 0 || y >= visited[0].size() ||
        visited[x][y] == 1) {
      return;
    }
    int cal = 0;
    int tmp = x;
    while (tmp) {
      cal += tmp % 10;
      tmp /= 10;
    }
    tmp = y;
    while (tmp) {
      cal += tmp % 10;
      tmp /= 10;
    }

    if (cal > k)
      return;
    visited[x][y] = 1;
    all++;
    dfs(visited, all, x + 1, y, k);
    dfs(visited, all, x - 1, y, k);
    dfs(visited, all, x, y + 1, k);
    dfs(visited, all, x, y - 1, k);
  }

  int movingCount(int m, int n, int k) {
    vector<vector<int>> visited(m, vector<int>(n, 0));
    int all = 0;
    dfs(visited, all, 0, 0, k);
    return all;
  }
};