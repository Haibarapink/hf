#include <assert.h>
#include <iostream>
#include <limits.h>
#include <queue>
#include <stdio.h>
#include <vector>

// 实现图的所有算法

class DirectGraph {
public:
  DirectGraph(int n) : grid(n, std::vector<int>(n, 0)) {}
  void add_edge(int u, int v, int w) { grid[u][v] = w; }
  int get_edge(int u, int v) { return grid[u][v]; }
  int size() { return grid.size(); }

  bool has_edge(int u, int v) { return grid[u][v] != 0; }

  void quick_add_edge(int src, std::vector<int> to) {
    for (auto i = 0; i < to.size(); ++i)
      add_edge(src, to[i], 1);
  }

  void quick_add_edge_with_weight(std::vector<std::vector<int>> edges) {
    for (const auto &i : edges) {
      add_edge(i[0], i[1], i[2]);
    }
  }
  void print() {
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid.size(); j++) {
        std::cout << grid[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<std::vector<int>> grid;
};

class UnDirectGraph {
  UnDirectGraph(int n) : grid(n, std::vector<int>(n, 0)) {}
  void add_edge(int u, int v, int w) { grid[u][v] = w; }
  int get_edge(int u, int v) const { return grid[u][v]; }
  int size() const { return grid.size(); }

  bool has_edge(int u, int v) const { return grid[u][v] != 0; }

  void print() const {
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid.size(); j++) {
        std::cout << grid[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<std::vector<int>> grid;
};

// 有向无权图单源最短路,实际上是求路径罢了
// 第一个返回是 dist距离 第二个返回是path
std::pair<std::vector<int>, std::vector<int>> Unweighed(DirectGraph &g,
                                                        int vetx) {
  std::vector<int> dist(g.size(), -1), path(g.size(), -1);
  std::queue<int> q;

  q.push(vetx);
  dist[vetx] = 0;
  path[vetx] = 0;
  while (!q.empty()) {
    auto cur_node = q.front();
    q.pop();
    for (int i = 0; i < g.size(); ++i) {
      if (g.has_edge(cur_node, i)) {
        if (dist[i] == -1) {
          dist[i] = dist[cur_node] + 1;
          path[i] = cur_node;
          q.push(i);
        }
      }
    }
  }

  // rov 优化掉了， 不需要move
  return {dist, path};
}

void TestUnWeighted() {
  DirectGraph g(8);
  // 陈越上面的例子
  g.quick_add_edge(1, {2, 4});
  g.quick_add_edge(2, {4, 5});
  g.quick_add_edge(3, {1, 6});
  g.quick_add_edge(4, {3, 6, 7, 5});
  g.quick_add_edge(5, {7});
  g.quick_add_edge(7, {6});
  auto res = Unweighed(g, 3);
  for (auto i : res.first) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  for (auto j : res.second) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}

// 有权的 单源最短路
std::pair<std::vector<int>, std::vector<int>> Dijkstra(DirectGraph &g,
                                                       int vetx) {
  std::vector<int> dist(g.size(), INT_MAX), path(g.size(), -1);
  std::vector<bool> visited(g.size(), false);
  dist[vetx] = 0;
  path[vetx] = 0;
  visited[vetx] = true;
  int V = -1, min_dist = INT_MAX;

  // init dist
  for (auto i = 0; i < g.size(); ++i) {
    if (i != vetx) {
      if (g.has_edge(vetx, i)) {
        dist[i] = g.get_edge(vetx, i);
        if (dist[i] < min_dist) {
          min_dist = dist[i];
          V = i;
        }
      }
    }
  }

  while (true) {
    V = -1;
    min_dist = INT_MAX;
    // find min v
    for (auto i = 0; i < g.size(); ++i) {
      if (!visited[i] && dist[i] != INT_MAX) {
        if (dist[i] < min_dist) {
          V = i;
          min_dist = dist[i];
        }
      }
    }

    // V don't exist
    if (V == -1)
      return {dist, path};

    // foreach the edges of V and update the distincts
    for (auto i = 0; i < g.size(); ++i) {
      if (g.has_edge(V, i) && !visited[i]) {
        if (dist[i] > g.get_edge(V, i) + min_dist) {
          dist[i] = g.get_edge(V, i) + min_dist;
          path[i] = V;
        }
      }
    }

    visited[V] = true;
  }

  return {dist, path};
}

void print_path(int vetex, int from, const std::vector<int> &path) {
  int to = from;
  while (to != -1) {
    std::cout << to << " <- ";
    to = path[to];
  }
  std::cout << vetex;
  std::cout << "\n";
}

void TestWeighted() {
  DirectGraph g(8);
  // 陈越上面的例子
  g.quick_add_edge_with_weight({{1, 4, 1},
                                {1, 2, 2},
                                {2, 4, 3},
                                {2, 5, 10},
                                {3, 1, 4},
                                {3, 6, 5},
                                {4, 3, 2},
                                {4, 5, 2},
                                {4, 6, 8},
                                {4, 7, 4},
                                {5, 7, 6},
                                {7, 6, 1}});
  auto res = Dijkstra(g, 1);
  print_path(1, 6, res.second);
}

// 有向图有环判定方法
// dfs
bool cycle_check_dfs(DirectGraph &d, int cur, std::vector<int> &visited) {
  visited[cur] = 1;
  for (auto i = 0; i < d.size(); ++i) {
    if (d.has_edge(cur, i)) {
      if (visited[i] == 1) {
        return true;
      }
      bool ok = cycle_check_dfs(d, i, visited);
      if (ok) {
        return true;
      }
    }
  }
  visited[cur] = 2;
  return false;
}

bool contain_cycle(DirectGraph &g) {
  std::vector<int> visited(g.size(), 0);
  for (auto i = 0; i < g.size(); ++i) {
    if (visited[i] == 0) {
      bool ok = cycle_check_dfs(g, i, visited);
      if (ok) {
        return true;
      }
    }
  }
  return false;
}

void TestCheckDirectedCycle() {
  DirectGraph g(8);
  g.quick_add_edge_with_weight({{1, 4, 1}, {1, 2, 2}, {2, 7, 1}, {7, 6, 1}});
  assert(!contain_cycle(g));
  g.add_edge(6, 1, 1);
  assert(contain_cycle(g));
}
int main(int, char **) {
  TestUnWeighted();
  TestWeighted();
  TestCheckDirectedCycle();
  return 0;
}