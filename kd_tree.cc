#include <algorithm>
#include <cmath>
#include <vector>

struct Point {
  std::vector<double> coords;
};

struct Node {
  Point point;
  Node *left;
  Node *right;
};

class KDTree {
public:
  KDTree(const std::vector<Point> &points) { root_ = buildTree(points, 0); }

  Point nearestNeighbor(const Point &query) {
    double bestDist = std::numeric_limits<double>::max();
    Point bestPoint;
    searchTree(root_, query, 0, bestDist, bestPoint);
    return bestPoint;
  }

private:
  Node *root_;

  Node *buildTree(const std::vector<Point> &points, int depth) {
    if (points.empty()) {
      return nullptr;
    }
    int axis = depth % points[0].coords.size();
    auto cmp = [axis](const Point &p1, const Point &p2) {
      return p1.coords[axis] < p2.coords[axis];
    };
    auto median = points.begin() + points.size() / 2;
    std::nth_element(points.begin(), median, points.end(), cmp);
    Node *node = new Node;
    node->point = *median;
    node->left =
        buildTree(std::vector<Point>(points.begin(), median), depth + 1);
    node->right =
        buildTree(std::vector<Point>(median + 1, points.end()), depth + 1);
    return node;
  }

  void searchTree(Node *node, const Point &query, int depth, double &bestDist,
                  Point &bestPoint) {
    if (node == nullptr) {
      return;
    }
    double dist = distance(node->point, query);
    if (dist < bestDist) {
      bestDist = dist;
      bestPoint = node->point;
    }
    int axis = depth % query.coords.size();
    double planeDist = query.coords[axis] - node->point.coords[axis];
    if (planeDist < 0) {
      searchTree(node->left, query, depth + 1, bestDist, bestPoint);
      if (planeDist * planeDist < bestDist) {
        searchTree(node->right, query, depth + 1, bestDist, bestPoint);
      }
    } else {
      searchTree(node->right, query, depth + 1, bestDist, bestPoint);
      if (planeDist * planeDist < bestDist) {
        searchTree(node->left, query, depth + 1, bestDist, bestPoint);
      }
    }
  }

  double distance(const Point &p1, const Point &p2) {
    double dist = 0;
    for (int i = 0; i < p1.coords.size(); ++i) {
      dist += (p1.coords[i] - p2.coords[i]) * (p1.coords[i] - p2.coords[i]);
    }
    return std::sqrt(dist);
  }
};

int main(int, char **) {}