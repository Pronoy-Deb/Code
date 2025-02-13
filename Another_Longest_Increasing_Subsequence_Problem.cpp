#include <bits/stdc++.h>
using namespace std;

struct Point {
    int64_t x, y;
};

// Function to find the LIS on the y-coordinates after sorting by x
int lis_2D(vector<Point>& points) {
    int n = points.size();
    if (n == 0) return 0;

    // Step 1: Sort by (x, y) ensuring x is strictly increasing
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y); // Strictly increasing x
    });

    // Step 2: Extract y-coordinates for LIS processing
    vector<int64_t> y_values;
    for (auto& p : points) y_values.push_back(p.y);

    // Step 3: Compute LIS on y-coordinates using upper_bound() for strict increasing order
    vector<int64_t> lis;
    for (int64_t y : y_values) {
        auto it = upper_bound(lis.begin(), lis.end(), y);
        if (it == lis.end()) lis.push_back(y);
        else *it = y; // Maintain the smallest possible y-value at this LIS length
    }

    return lis.size();
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    cout << lis_2D(points) << endl;
    return 0;
}
