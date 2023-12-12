#include <vector>

using namespace std;

class disjoint_set {
public:
  int find(int x) {
    while (x != u[x])
      x = u[x];
    return x;
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    u[x] = y;
    return true;
  }

  bool connected(int x, int y) { return find(x) == find(y); }

private:
  vector<int> u;
};

int main(int, char **) {}