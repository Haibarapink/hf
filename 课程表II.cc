class Solution {
private:
  vector<vector<int>> edges;
  vector<int> indeg;
  vector<int> result;

public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    edges.resize(numCourses);
    indeg.resize(numCourses);
    for (const auto &info : prerequisites) {
      edges[info[1]].push_back(info[0]);
      ++indeg[info[0]];
    }

    queue<int> q;
    // 将所有入度为 0 的节点放入队列中
    for (int i = 0; i < numCourses; ++i) {
      if (indeg[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      // 从队首取出一个节点
      int u = q.front();
      q.pop();
      // 放入答案中
      result.push_back(u);
      for (int v : edges[u]) {
        --indeg[v];
        // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
        if (indeg[v] == 0) {
          q.push(v);
        }
      }
    }

    if (result.size() != numCourses) {
      return {};
    }
    return result;
  }
};
