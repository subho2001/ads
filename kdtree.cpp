#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    vector<int> coords;
};

struct Node {
    Point point;
    Node* left;
    Node* right;
    int axis;

    Node(Point p) : point(p), left(nullptr), right(nullptr), axis(0) {}
};

class KDTree {
private:
    Node* root;

    Node* buildTree(vector<Point>& points, int start, int end, int axis) {
        if (start > end) return nullptr;

        int mid = (start + end) / 2;

        if (axis == points[mid].coords.size()) axis = 0;

        auto cmp = [axis](const Point& a, const Point& b) {
            return a.coords[axis] < b.coords[axis];
        };

        nth_element(points.begin() + start, points.begin() + mid, points.begin() + end + 1, cmp);

        Node* newNode = new Node(points[mid]);
        newNode->axis = axis;
        newNode->left = buildTree(points, start, mid - 1, axis + 1);
        newNode->right = buildTree(points, mid + 1, end, axis + 1);

        return newNode;
    }

    void searchNearestNeighbor(Node* node, const Point& target, Node*& best, double& bestDist) {
        if (node == nullptr) return;

        double dist = 0;
        for (int i = 0; i < target.coords.size(); ++i) {
            dist += (target.coords[i] - node->point.coords[i]) * (target.coords[i] - node->point.coords[i]);
        }

        if (best == nullptr || dist < bestDist) {
            best = node;
            bestDist = dist;
        }

        int axis = node->axis;
        double diff = target.coords[axis] - node->point.coords[axis];

        if (diff < 0) {
            searchNearestNeighbor(node->left, target, best, bestDist);
            if (diff * diff < bestDist)
                searchNearestNeighbor(node->right, target, best, bestDist);
        }
        else {
            searchNearestNeighbor(node->right, target, best, bestDist);
            if (diff * diff < bestDist)
                searchNearestNeighbor(node->left, target, best, bestDist);
        }
    }

public:
    KDTree(vector<Point>& points) {
        root = buildTree(points, 0, points.size() - 1, 0);
    }

    Node* nearestNeighbor(const Point& target) {
        Node* best = nullptr;
        double bestDist = numeric_limits<double>::infinity();
        searchNearestNeighbor(root, target, best, bestDist);
        return best;
    }
};

int main() {
    vector<Point> points = {
        {{2, 3}},
        {{5, 4}},
        {{9, 6}},
        {{4, 7}},
        {{8, 1}},
        {{7, 2}}
    };

    KDTree kdTree(points);

    Point target = {{9, 5}};
    Node* nearest = kdTree.nearestNeighbor(target);
    
    cout << "Nearest neighbor to target (" << target.coords[0] << ", " << target.coords[1] << "): (";
    for (int i = 0; i < nearest->point.coords.size(); ++i) {
        cout << nearest->point.coords[i];
        if (i < nearest->point.coords.size() - 1) cout << ", ";
    }
    cout << ")" << endl;

    return 0;
}
