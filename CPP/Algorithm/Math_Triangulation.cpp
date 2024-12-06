Math Triangulation:
class point {
   public:
    int x, y;
    point(int a, int b) {
        x = a; y = b;
    }
};
int isLeft(point A, point B, point C) {
    int area = A.x * (B.y - C.y) - A.y * (B.x - C.x) + (B.x * C.y - C.x * B.y);
    if (area < 0) return area;
    else return area;
}
// input the all point(x,y) and give the area of the polygon
float area_of_a_polygon(int n) {
    if (n < 3) { return 0; }
    int x1, y1, x2, y2, x, y; float area = 0, now;
    cin >> x1 >> y1; x = x1; y = y1;
    for (int i = 1; i < n; i++) {
        cin >> x2 >> y2;
        area = area + ((float)(x1 * y2 - x2 * y1) / 2);
        cout << area << "\n"; x1 = x2; y1 = y2;
    }
    cin >> x2 >> y2;
    area = area + ((float)(x2 * y - x * y2) / 2);
    return abs(area);
}
