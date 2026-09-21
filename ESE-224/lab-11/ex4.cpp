#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>   
using namespace std;

struct Point {
    int x;
    int y;
    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
};

int distanceSquared(const Point& p) {
    return p.x * p.x + p.y * p.y;
}

struct Node {
    int dist;
    Point p;
    Node(int d, const Point& point) : dist(d), p(point) {}
};

struct Compare {
    bool operator()(const Node& a, const Node& b) const {
        return a.dist < b.dist;
    }
};

vector<Point> findClosestKPoints(const vector<Point>& points, int k) {
    priority_queue<Node, vector<Node>, Compare> maxHeap;

    for (const auto& pt : points) {
        int d = distanceSquared(pt);
        if ((int)maxHeap.size() < k) {
            maxHeap.emplace(d, pt);
        } else if (d < maxHeap.top().dist) {
            maxHeap.pop();
            maxHeap.emplace(d, pt);
        }
    }

    vector<Point> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top().p);
        maxHeap.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<Point> points = {
        Point(1, 2),
        Point(4, 6),
        Point(3, 3),
        Point(0, 1),
        Point(2, 1)
    };

    int k = 3;

    vector<Point> closest = findClosestKPoints(points, k);

    cout << "Input Points: ";
    for (const auto& p : points) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    cout << "\n";

    cout << "k = " << k << "\n";
    cout << "Output Points: ";
    for (const auto& p : closest) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    cout << "\n";

    return 0;
}
