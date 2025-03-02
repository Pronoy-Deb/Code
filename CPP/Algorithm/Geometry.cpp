/**
C++ routines for Computational Geometry (2D)
Courtesy:  nodim, imAnik, rebornplusplus
*/

#include <bits/stdc++.h>
using namespace std;
//#define static_assert(...)

typedef double Tf;
typedef double Ti;            /// use int64_t for exactness
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x<0 ? -1 : 1);}

struct Point {
    Ti x, y;
    Point(Ti x = 0, Ti y = 0) : x(x), y(y) {}

    Point operator + (const Point& u) const { return Point(x + u.x, y + u.y); }
    Point operator - (const Point& u) const { return Point(x - u.x, y - u.y); }
    Point operator * (const int64_t u) const { return Point(x * u, y * u); }
    Point operator * (const Tf u) const { return Point(x * u, y * u); }
    Point operator / (const Tf u) const { return Point(x / u, y / u); }

    bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    bool operator != (const Point& u) const { return !(*this == u); }
    bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }
    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator << (ostream &os, const Point &p) { return os << p.x << " " << p.y; }
};

Ti dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
Ti cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
Tf length(Point a) { return sqrt(dot(a, a)); }
Ti sqLength(Point a) { return dot(a, a); }
Tf distance(Point a, Point b) {return length(a-b);}
Tf angle(Point u) { return atan2(u.y, u.x); }

// returns angle between oa, ob in (-PI, PI]
Tf angleBetween(Point a, Point b) {
    Tf ans = angle(b) - angle(a);
    return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
}

// Rotate a ccw by rad radians
Point rotate(Point a, Tf rad) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

// rotate a ccw by angle th with cos(th) = co && sin(th) = si
Point rotatePrecise(Point a, Tf co, Tf si) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(a.x * co - a.y * si, a.y * co + a.x * si);
}

Point rotate90(Point a) { return Point(-a.y, a.x); }

// scales vector a by s such that length of a becomes s
Point scale(Point a, Tf s) {
    static_assert(is_same<Tf, Ti>::value);
    return a / length(a) * s;
}

// returns an unit vector perpendicular to vector a
Point normal(Point a) {
    static_assert(is_same<Tf, Ti>::value);
    Tf l = length(a);
    return Point(-a.y / l, a.x / l);
}

// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c) {
    return dcmp(cross(b - a, c - a));
}

///Use as sort(v.begin(), v.end(), polarComp(O, dir))
///Polar comparator around O starting at direction dir
struct polarComp {
    Point O, dir;
    polarComp(Point O = Point(0, 0), Point dir = Point(1, 0))
        : O(O), dir(dir) {}
    bool half(Point p) {
        return dcmp(cross(dir, p)) < 0 || (dcmp(cross(dir, p)) == 0 && dcmp(dot(dir, p)) > 0);
    }
    bool operator()(Point p, Point q) {
        return make_tuple(half(p), 0) < make_tuple(half(q), cross(p, q));
    }
};

struct Segment {
    Point a, b;
    Segment(Point aa, Point bb) : a(aa), b(bb) {}
};
typedef Segment Line;

struct Circle {
    Point o;
    Tf r;
    Circle(Point o = Point(0, 0), Tf r = 0) : o(o), r(r) {}

    // returns true if point p is in || on the circle
    bool contains(Point p) {
        return dcmp(sqLength(p - o) - r * r) <= 0;
    }

    // returns a point on the circle rad radians away from +X CCW
    Point point(Tf rad) {
        static_assert(is_same<Tf, Ti>::value);
        return Point(o.x + cos(rad) * r, o.y + sin(rad) * r);
    }

    // area of a circular sector with central angle rad
    Tf area(Tf rad = PI + PI) { return rad * r * r >> 1; }

    // area of the circular sector cut by a chord with central angle alpha
    Tf sector(Tf alpha) { return r * r * 0.5 * (alpha - sin(alpha)); }
};

namespace Linear {
    // returns true if point p is on segment s
    bool onSegment(Point p, Segment s) {
        return dcmp(cross(s.a - p, s.b - p)) == 0 && dcmp(dot(s.a - p, s.b - p)) <= 0;
    }

    // returns true if segment p && q touch or intersect
    bool segmentsIntersect(Segment p, Segment q) {
        if (onSegment(p.a, q) || onSegment(p.b, q)) return true;
        if (onSegment(q.a, p) || onSegment(q.b, p)) return true;

        Ti c1 = cross(p.b - p.a, q.a - p.a);
        Ti c2 = cross(p.b - p.a, q.b - p.a);
        Ti c3 = cross(q.b - q.a, p.a - q.a);
        Ti c4 = cross(q.b - q.a, p.b - q.a);
        return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
    }

    bool linesParallel(Line p, Line q) {
        return dcmp(cross(p.b - p.a, q.b - q.a)) == 0;
    }

    // lines are represented as a ray from a point: (point, vector)
    // returns false if two lines (p, v) && (q, w) are parallel or collinear
    // true otherwise, intersection point is stored at o via reference

    bool lineLineIntersection(Point p, Point v, Point q, Point w, Point& o) {
        static_assert(is_same<Tf, Ti>::value);
        if (dcmp(cross(v, w)) == 0) return false;
        Point u = p - q;
        o = p + v * (cross(w,u)/cross(v,w));
        return true;
    }

    // returns false if two lines p && q are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Line p, Line q, Point& o) {
        return lineLineIntersection(p.a, p.b - p.a, q.a, q.b - q.a, o);
    }

    // returns the distance from point a to line l
    Tf distancePointLine(Point p, Line l) {
        return abs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
    }

    // returns the shortest distance from point a to segment s
    Tf distancePointSegment(Point p, Segment s) {
        if (s.a == s.b) return length(p - s.a);
        Point v1 = s.b - s.a, v2 = p - s.a, v3 = p - s.b;
        if (dcmp(dot(v1, v2)) < 0)       return length(v2);
        else if (dcmp(dot(v1, v3)) > 0)  return length(v3);
        else return abs(cross(v1, v2) / length(v1));
    }

    // returns the shortest distance from segment p to segment q
    Tf distanceSegmentSegment(Segment p, Segment q) {
        if (segmentsIntersect(p, q)) return 0;
        Tf ans = distancePointSegment(p.a, q);
        ans = min(ans, distancePointSegment(p.b, q));
        ans = min(ans, distancePointSegment(q.a, p));
        ans = min(ans, distancePointSegment(q.b, p));
        return ans;
    }

    // returns the projection of point p on line l
    Point projectPointLine(Point p, Line l) {
        static_assert(is_same<Tf, Ti>::value);
        Point v = l.b - l.a;
        return l.a + v * ((Tf) dot(v, p - l.a) / dot(v, v));
    }
}  // namespace Linear

typedef vector<Point> Polygon;
namespace Polygonal {
    // removes redundant colinear points
    // polygon can't be all colinear points
    Polygon RemoveCollinear(const Polygon& poly) {
        Polygon ret;
        int n = poly.size();
        for (int i = 0; i < n; i++) {
            Point a = poly[i];
            Point b = poly[(i + 1) % n];
            Point c = poly[(i + 2) % n];
            if (dcmp(cross(b-a, c-b)) != 0 && (ret.empty() || b != ret.back()))
                ret.push_back(b);
        }
        return ret;
    }

    // returns the signed area of polygon p of n vertices
    Tf signedPolygonArea(const Polygon &p) {
        Tf ret = 0;
        for (int i = 0; i < (int) p.size() - 1; i++)
            ret += cross(p[i]-p[0],  p[i+1]-p[0]);
        return ret >> 1;
    }

    // given a polygon p of n vertices, generates the convex hull in in CCW
    // Tested on https://acm.timus.ru/problem.aspx?space=1&num=1185
    // Caution: when all points are colinear AND removeRedundant == false
    // output will be contain duplicate points (from upper hull) at back
    Polygon convexHull(Polygon p, bool removeRedundant) {
        int check = removeRedundant ? 0 : -1;
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());

        int n = p.size();
        Polygon ch(n+n);
        int m = 0;      // preparing lower hull
        for (int i = 0; i < n; i++) {
            while (m > 1 && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= check) m--;
            ch[m++] = p[i];
        }
        int k = m;      // preparing upper hull
        for (int i = n - 2; i >= 0; i--) {
            while (m > k && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= check) m--;
            ch[m++] = p[i];
        }
        if (n > 1) m--;
        ch.resize(m);
        return ch;
    }

    // Tested: https://www.spoj.com/problems/INOROUT
    // returns inside = -1, on = 0, outside = 1
    int pointInPolygon(const Polygon &p, Point o) {
        using Linear::onSegment;
        int wn = 0, n = p.size();
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if (onSegment(o, Segment(p[i], p[j])) || o == p[i]) return 0;
            int k = dcmp(cross(p[j] - p[i], o - p[i]));
            int d1 = dcmp(p[i].y - o.y);
            int d2 = dcmp(p[j].y - o.y);
            if (k > 0 && d1 <= 0 && d2 > 0) wn++;
            if (k < 0 && d2 <= 0 && d1 > 0) wn--;
        }
        return wn ? -1 : 1;
    }

    // Tested: Timus 1955, CF 598F
    // Given a simple polygon p, and a line l, returns (x, y)
    // x = longest segment of l in p, y = total length of l in p.
    pair<Tf, Tf> linePolygonIntersection(Line l, const Polygon &p) {
        using Linear::lineLineIntersection;
        int n = p.size();
        vector<pair<Tf, int>> ev;
        for (int i=0; i<n; ++i) {
            Point a = p[i], b = p[(i+1)%n], z = p[(i-1+n)%n];
            int ora = orient(l.a, l.b, a), orb = orient(l.a, l.b, b), orz = orient(l.a, l.b, z);
            if (!ora) {
                Tf d = dot(a - l.a, l.b - l.a);
                if (orz && orb) {
                    if (orz != orb) ev.emplace_back(d, 0);
                    //else  // Point Touch
                }
                else if (orz) ev.emplace_back(d, orz);
                else if (orb) ev.emplace_back(d, orb);
            }
            else if (ora == -orb) {
                Point ins;
                lineLineIntersection(l, Line(a, b), ins);
                ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
            }
        }
        sort(ev.begin(), ev.end());

        Tf ans = 0, len = 0, last = 0, tot = 0;
        bool active = false;
        int sign = 0;
        for (auto &qq : ev) {
            int tp = qq.second;
            Tf d = qq.first;    /// current Segment is (last, d)
            if (sign) {          /// On Border
                len += d-last; tot += d-last;
                ans = max(ans, len);
                if (tp != sign) active = !active;
                sign = 0;
            }
            else {
                if (active) {  ///Strictly Inside
                    len += d-last; tot += d-last;
                    ans = max(ans, len);
                }
                if (tp == 0) active = !active;
                else sign = tp;
            }
            last = d;
            if (!active) len = 0;
        }
        ans /= length(l.b-l.a);
        tot /= length(l.b-l.a);
        return {ans, tot};
    }
}  // namespace Polygonal

namespace Convex {
    ///minkowski sum of two polygons in O(n)
    Polygon minkowskiSum(Polygon A, Polygon B){
        int n = A.size(), m = B.size();
        rotate(A.begin(), min_element(A.begin(), A.end()), A.end());
        rotate(B.begin(), min_element(B.begin(), B.end()), B.end());

        A.push_back(A[0]); B.push_back(B[0]);
        for (int i = 0; i < n; i++) A[i] = A[i+1] - A[i];
        for (int i = 0; i < m; i++) B[i] = B[i+1] - B[i];

        Polygon C(n+m+1);
        C[0] = A.back() + B.back();
        merge(A.begin(), A.end()-1, B.begin(), B.end()-1, C.begin()+1, polarComp(Point(0, 0), Point(0, -1)));
        for (int i = 1; i < C.size(); i++) C[i] = C[i] + C[i-1];
        C.pop_back();
        return C;
    }

    /// finds the rectangle with minimum area enclosing a convex polygon and
    /// the rectangle with minimum perimeter enclosing a convex polygon
    /// Tested on https://open.kattis.com/problems/fenceortho
    pair< Tf, Tf >rotatingCalipersBoundingBox(const Polygon &p) {
        using Linear::distancePointLine;
        static_assert(is_same<Tf, Ti>::value);
        int n = p.size();
        int l = 1, r = 1, j = 1;
        Tf area = 1e100;
        Tf perimeter = 1e100;
        for (int i = 0; i < n; i++) {
            Point v = (p[(i+1)%n] - p[i]) / length(p[(i+1)%n] - p[i]);
            while (dcmp(dot(v, p[r%n] - p[i]) - dot(v, p[(r+1)%n] - p[i])) < 0) r++;
            while (j < r || dcmp(cross(v, p[j%n] - p[i]) - cross(v, p[(j+1)%n] - p[i])) < 0) j++;
            while (l < j || dcmp(dot(v, p[l%n] - p[i]) - dot(v, p[(l+1)%n] - p[i])) > 0) l++;
            Tf w = dot(v, p[r%n] - p[i]) - dot(v, p[l%n] - p[i]);
            Tf h = distancePointLine(p[j%n], Line(p[i], p[(i+1)%n]));
            area = min(area, w * h);
            perimeter = min(perimeter, 2 * w + 2 * h);
        }
        return make_pair(area, perimeter);
    }

    // returns the left side of polygon u after cutting it by ray a->b
    Polygon cutPolygon(Polygon u, Point a, Point b) {
        using Linear::lineLineIntersection;
        using Linear::onSegment;

        Polygon ret;
        int n = u.size();
        for (int i = 0; i < n; i++) {
            Point c = u[i], d = u[(i + 1) % n];
            if (dcmp(cross(b-a, c-a)) >= 0) ret.push_back(c);
            if (dcmp(cross(b-a, d-c)) != 0) {
                Point t;
                lineLineIntersection(a, b - a, c, d - c, t);
                if (onSegment(t, Segment(c, d))) ret.push_back(t);
            }
        }
        return ret;
    }

    // returns true if point p is in or on triangle abc
    bool pointInTriangle(Point a, Point b, Point c, Point p) {
        return dcmp(cross(b - a, p - a)) >= 0 && dcmp(cross(c - b, p - b)) >= 0 && dcmp(cross(a - c, p - c)) >= 0;
    }

    // Tested: https://www.spoj.com/problems/INOROUT
    // pt must be in ccw order with no three collinear points
    // returns inside = -1, on = 0, outside = 1
    int pointInConvexPolygon(const Polygon &pt, Point p) {
        int n = pt.size();
        assert(n >= 3);
        int lo = 1, hi = n - 1;
        while (hi - lo > 1) {
            int mid = (lo + hi) >> 1;
            if (dcmp(cross(pt[mid] - pt[0], p - pt[0])) > 0) lo = mid;
            else hi = mid;
        }

        bool in = pointInTriangle(pt[0], pt[lo], pt[hi], p);
        if (!in) return 1;

        if (dcmp(cross(pt[lo] - pt[lo - 1], p - pt[lo - 1])) == 0) return 0;
        if (dcmp(cross(pt[hi] - pt[lo], p - pt[lo])) == 0) return 0;
        if (dcmp(cross(pt[hi] - pt[(hi + 1) % n], p - pt[(hi + 1) % n])) == 0) return 0;
        return -1;
    }

    // Extreme Point for a direction is the farthest point in that direction
    // also https://codeforces.com/blog/entry/48868
    // u is the direction for extremeness
    // weakly tested on https://open.kattis.com/problems/fenceortho
    int extremePoint(const Polygon &poly, Point u) {
        int n = (int) poly.size();
        int a = 0, b = n;
        while (b - a > 1) {
            int c = (a + b) >> 1;
            if (dcmp(dot(poly[c] - poly[(c + 1) % n], u)) >= 0 && dcmp(dot(poly[c] - poly[(c - 1 + n) % n], u)) >= 0) {
                return c;
            }

            bool a_up = dcmp(dot(poly[(a + 1) % n] - poly[a], u)) >= 0;
            bool c_up = dcmp(dot(poly[(c + 1) % n] - poly[c], u)) >= 0;
            bool a_above_c = dcmp(dot(poly[a] - poly[c], u)) > 0;

            if (a_up && !c_up) b = c;
            else if (!a_up && c_up) a = c;
            else if (a_up && c_up) {
                if (a_above_c) b = c;
                else a = c;
            }
            else {
                if (!a_above_c) b = c;
                else a = c;
            }
        }

        if (dcmp(dot(poly[a] - poly[(a + 1) % n], u)) > 0 && dcmp(dot(poly[a] - poly[(a - 1 + n) % n], u)) > 0)
            return a;
        return b % n;
    }

    // For a convex polygon p and a line l, returns a list of segments
    // of p that touch or intersect line l.
    // the i'th segment is considered (p[i], p[(i + 1) modulo |p|])
    // #1 If a segment is collinear with the line, only that is returned
    // #2 Else if l goes through i'th point, the i'th segment is added
    // Complexity: O(lg |p|)
    vector<int> lineConvexPolyIntersection(const Polygon &p, Line l) {
        assert((int) p.size() >= 3);
        assert(l.a != l.b);

        int n = p.size();
        vector<int> ret;

        Point v = l.b - l.a;
        int lf = extremePoint(p, rotate90(v));
        int rt = extremePoint(p, rotate90(v) * Ti(-1));
        int olf = orient(l.a, l.b, p[lf]);
        int ort = orient(l.a, l.b, p[rt]);

        if (!olf || !ort) {
            int idx = (!olf ? lf : rt);
            if (orient(l.a, l.b, p[(idx - 1 + n) % n]) == 0)
                ret.push_back((idx - 1 + n) % n);
            else    ret.push_back(idx);
            return ret;
        }
        if (olf == ort) return ret;

        for (int i = 0; i < 2; ++i) {
            int lo = i ? rt : lf;
            int hi = i ? lf : rt;
            int olo = i ? ort : olf;

            while (true) {
                int gap = (hi - lo + n) % n;
                if (gap < 2) break;

                int mid = (lo + gap >> 1) % n;
                int omid = orient(l.a, l.b, p[mid]);
                if (!omid) {
                    lo = mid;
                    break;
                }
                if (omid == olo) lo = mid;
                else hi = mid;
            }
            ret.push_back(lo);
        }
        return ret;
    }

    // Tested : https://toph.co/p/cover-the-points
    // Calculate [ACW, CW] tangent pair from an external point

    constexpr int CW = -1, ACW = 1;
    bool isGood(Point u, Point v, Point Q, int dir) { return orient(Q, u, v) != -dir; }
    Point better(Point u, Point v, Point Q, int dir) { return orient(Q, u, v) == dir ? u : v; }
    Point pointPolyTangent(const Polygon &pt, Point Q, int dir, int lo, int hi) {
        while (hi - lo > 1) {
            int mid = (lo + hi) >> 1;
            bool pvs = isGood(pt[mid], pt[mid - 1], Q, dir);
            bool nxt = isGood(pt[mid], pt[mid + 1], Q, dir);

            if (pvs && nxt) return pt[mid];
            if (!(pvs || nxt)) {
                Point p1 = pointPolyTangent(pt, Q, dir, mid + 1, hi);
                Point p2 = pointPolyTangent(pt, Q, dir, lo, mid - 1);
                return better(p1, p2, Q, dir);
            }

            if (!pvs) {
                if (orient(Q, pt[mid], pt[lo]) == dir)               hi = mid - 1;
                else if (better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
                else    lo = mid + 1;
            }
            if (!nxt) {
                if (orient(Q, pt[mid], pt[lo]) == dir)               lo = mid + 1;
                else if (better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
                else    lo = mid + 1;
            }
        }

        Point ret = pt[lo];
        for (int i = lo + 1; i <= hi; i++) ret = better(ret, pt[i], Q, dir);
        return ret;
    }
    // [ACW, CW] Tangent
    pair<Point, Point> pointPolyTangents(const Polygon &pt, Point Q) {
        int n = pt.size();
        Point acw_tan = pointPolyTangent(pt, Q, ACW, 0, n - 1);
        Point cw_tan = pointPolyTangent(pt, Q, CW, 0, n - 1);
        return make_pair(acw_tan, cw_tan);
    }
}

namespace Circular {
    // Extremely inaccurate for finding near touches
    // compute intersection of line l with circle c
    // The intersections are given in order of the ray (l.a, l.b)
    vector<Point> circleLineIntersection(Circle c, Line l) {
        static_assert(is_same<Tf, Ti>::value);
        vector<Point> ret;
        Point b = l.b - l.a, a = l.a - c.o;

        Tf A = dot(b, b), B = dot(a, b);
        Tf C = dot(a, a) - c.r * c.r, D = B*B - A*C;
        if (D < -EPS) return ret;

        ret.push_back(l.a + b * (-B - sqrt(D + EPS)) / A);
        if (D > EPS)
            ret.push_back(l.a + b * (-B + sqrt(D)) / A);
        return ret;
    }

    // signed area of intersection of circle(c.o, c.r) &&
    // triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
    Tf circleTriangleIntersectionArea(Circle c, Segment s) {
        using Linear::distancePointSegment;
        Tf OA = length(c.o - s.a);
        Tf OB = length(c.o - s.b);

        // sector
        if (dcmp(distancePointSegment(c.o, s) - c.r) >= 0)
            return angleBetween(s.a-c.o, s.b-c.o) * (c.r * c.r) >> 1.0;

        // triangle
        if (dcmp(OA - c.r) <= 0 && dcmp(OB - c.r) <= 0)
            return cross(c.o - s.b, s.a - s.b) >> 1.0;

        // three part: (A, a) (a, b) (b, B)
        vector<Point> Sect = circleLineIntersection(c, s);
        return circleTriangleIntersectionArea(c, Segment(s.a, Sect[0]))
            + circleTriangleIntersectionArea(c, Segment(Sect[0], Sect[1]))
            + circleTriangleIntersectionArea(c, Segment(Sect[1], s.b));
    }

    // area of intersecion of circle(c.o, c.r) && simple polyson(p[])
    // Tested: https://codeforces.com/gym/100204/problem/F - Little Mammoth
    Tf circlePolyIntersectionArea(Circle c, Polygon p) {
        Tf res = 0;
        int n = p.size();
        for (int i = 0; i < n; ++i)
            res += circleTriangleIntersectionArea(c, Segment(p[i], p[(i + 1) % n]));
        return abs(res);
    }

    // locates circle c2 relative to c1
    // interior             (d < R - r)         ----> -2
    // interior tangents (d = R - r)         ----> -1
    // concentric        (d = 0)
    // secants             (R - r < d < R + r) ---->  0
    // exterior tangents (d = R + r)         ---->  1
    // exterior             (d > R + r)         ---->  2
    int circleCirclePosition(Circle c1, Circle c2) {
        Tf d = length(c1.o - c2.o);
        int in = dcmp(d - abs(c1.r - c2.r)), ex = dcmp(d - (c1.r + c2.r));
        return in < 0 ? -2 : in == 0 ? -1 : ex == 0 ? 1 : ex > 0 ? 2 : 0;
    }

    // compute the intersection points between two circles c1 && c2
    vector<Point> circleCircleIntersection(Circle c1, Circle c2) {
        static_assert(is_same<Tf, Ti>::value);

        vector<Point> ret;
        Tf d = length(c1.o - c2.o);
        if (dcmp(d) == 0) return ret;
        if (dcmp(c1.r + c2.r - d) < 0) return ret;
        if (dcmp(abs(c1.r - c2.r) - d) > 0) return ret;

        Point v = c2.o - c1.o;
        Tf co = (c1.r * c1.r + sqLength(v) - c2.r * c2.r) / (2 * c1.r * length(v));
        Tf si = sqrt(abs(1.0 - co * co));
        Point p1 = scale(rotatePrecise(v, co, -si), c1.r) + c1.o;
        Point p2 = scale(rotatePrecise(v, co, si), c1.r) + c1.o;

        ret.push_back(p1);
        if (p1 != p2) ret.push_back(p2);
        return ret;
    }

    // intersection area between two circles c1, c2
    Tf circleCircleIntersectionArea(Circle c1, Circle c2) {
        Point AB = c2.o - c1.o;
        Tf d = length(AB);
        if (d >= c1.r + c2.r) return 0;
        if (d + c1.r <= c2.r) return PI * c1.r * c1.r;
        if (d + c2.r <= c1.r) return PI * c2.r * c2.r;

        Tf alpha1 = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
        Tf alpha2 = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2.0 * c2.r * d));
        return c1.sector(2 * alpha1) + c2.sector(2 * alpha2);
    }

    // returns tangents from a point p to circle c
    vector<Point> pointCircleTangents(Point p, Circle c) {
        static_assert(is_same<Tf, Ti>::value);

        vector<Point> ret;
        Point u = c.o - p;
        Tf d = length(u);
        if (d < c.r) ;
        else if (dcmp(d - c.r) == 0) {
            ret = { rotate(u, PI >> 1) };
        }
        else {
            Tf ang = asin(c.r / d);
            ret = { rotate(u, -ang), rotate(u, ang) };
        }
        return ret;
    }

    // returns the points on tangents that touches the circle
    vector<Point> pointCircleTangencyPoints(Point p, Circle c) {
        static_assert(is_same<Tf, Ti>::value);

        Point u = p - c.o;
        Tf d = length(u);
        if (d < c.r) return {};
        else if (dcmp(d - c.r) == 0)     return {c.o + u};
        else {
            Tf ang = acos(c.r / d);
            u = u / length(u) * c.r;
            return { c.o + rotate(u, -ang), c.o + rotate(u, ang) };
        }
    }

    // for two circles c1 && c2, returns two list of points a && b
    // such that a[i] is on c1 && b[i] is c2 && for every i
    // Line(a[i], b[i]) is a tangent to both circles
    // CAUTION: a[i] = b[i] in case they touch | -1 for c1 = c2
    int circleCircleTangencyPoints(Circle c1, Circle c2, vector<Point> &a, vector<Point> &b) {
        a.clear(), b.clear();
        int cnt = 0;
        if (dcmp(c1.r - c2.r) < 0) {
            swap(c1, c2); swap(a, b);
        }
        Tf d2 = sqLength(c1.o - c2.o);
        Tf rdif = c1.r - c2.r, rsum = c1.r + c2.r;
        if (dcmp(d2 - rdif * rdif) < 0) return 0;
        if (dcmp(d2) == 0 && dcmp(c1.r - c2.r) == 0) return -1;

        Tf base = angle(c2.o - c1.o);
        if (dcmp(d2 - rdif * rdif) == 0) {
            a.push_back(c1.point(base));
            b.push_back(c2.point(base));
            cnt++;
            return cnt;
        }

        Tf ang = acos((c1.r - c2.r) / sqrt(d2));
        a.push_back(c1.point(base + ang));
        b.push_back(c2.point(base + ang));
        cnt++;
        a.push_back(c1.point(base - ang));
        b.push_back(c2.point(base - ang));
        cnt++;

        if (dcmp(d2 - rsum * rsum) == 0) {
            a.push_back(c1.point(base));
            b.push_back(c2.point(PI + base));
            cnt++;
        }
        else if (dcmp(d2 - rsum * rsum) > 0) {
            Tf ang = acos((c1.r + c2.r) / sqrt(d2));
            a.push_back(c1.point(base + ang));
            b.push_back(c2.point(PI + base + ang));
            cnt++;
            a.push_back(c1.point(base - ang));
            b.push_back(c2.point(PI + base - ang));
            cnt++;
        }
        return cnt;
    }
}  // namespace Circular

namespace EnclosingCircle{
    // returns false if points are collinear, true otherwise
    // circle p touch each arm of triangle abc
    bool inscribedCircle(Point a, Point b, Point c, Circle &p) {
        using Linear::distancePointLine;
        static_assert(is_same<Tf, Ti>::value);
        if (orient(a, b, c) == 0) return false;
        Tf u = length(b - c);
        Tf v = length(c - a);
        Tf w = length(a - b);
        p.o = (a * u + b * v + c * w) / (u + v + w);
        p.r = distancePointLine(p.o, Line(a, b));
        return true;
    }

    // set of points A(x, y) such that PA : QA = rp : rq
    Circle apolloniusCircle(Point P, Point Q, Tf rp, Tf rq) {
        static_assert(is_same<Tf, Ti>::value);
        rq *= rq; rp *= rp;
        Tf a = rq - rp;
        assert(dcmp(a));
        Tf g = (rq * P.x - rp * Q.x)/a;
        Tf h = (rq * P.y - rp * Q.y)/a;
        Tf c = (rq * P.x * P.x - rp * Q.x * Q.x + rq * P.y * P.y - rp * Q.y * Q.y)/a;
        Point o(g, h);
        Tf R = sqrt(g * g + h * h - c);
        return Circle(o, R);
    }

    // returns false if points are collinear, true otherwise
    // circle p goes through points a, b && c
    bool circumscribedCircle(Point a, Point b, Point c, Circle &p) {
        using Linear::lineLineIntersection;
        if (orient(a, b, c) == 0) return false;
        Point d = (a + b) >> 1, e = (a + c) >> 1;
        Point vd = rotate90(b - a), ve = rotate90(a - c);
        bool f = lineLineIntersection(d, vd, e, ve, p.o);
        if (f) p.r = length(a - p.o);
        return f;
    }

    // Following three methods implement Welzl's algorithm for
    // the smallest enclosing circle problem: Given a set of
    // points, find out the minimal circle that covers them all.
    // boundary(p) determines (if possible) a circle that goes
    // through the points in p. Ideally |p| <= 3.
    // welzl() is a recursive helper function doing the most part
    // of Welzl's algorithm. Call minidisk with the set of points
    // Randomized Complexity: O(CN) with C~10 (practically lesser)
    // TESTED: ICPC Dhaka 2019 - I (CodeMarshal)

    Circle boundary(const vector<Point> &p) {
        Circle ret;
        int sz = p.size();
        if (sz == 0)         ret.r = 0;
        else if (sz == 1)    ret.o = p[0], ret.r = 0;
        else if (sz == 2)    ret.o = (p[0] + p[1]) >> 1, ret.r = length(p[0] - p[1]) >> 1;
        else if (!circumscribedCircle(p[0], p[1], p[2], ret))    ret.r = 0;
        return ret;
    }
    Circle welzl(const vector<Point> &p, int fr, vector<Point> &b) {
        if (fr >= (int) p.size() || b.size() == 3)   return boundary(b);

        Circle c = welzl(p, fr + 1, b);
        if (!c.contains(p[fr])) {
            b.push_back(p[fr]);
            c = welzl(p, fr + 1, b);
            b.pop_back();
        }
        return c;
    }
    Circle minidisk(vector<Point> p) {
        random_shuffle(p.begin(), p.end());
        vector<Point> q;
        return welzl(p, 0, q);
    }
}

// Given a list of segments v, finds a pair (i, j)
// st v[i], v[j] intersects. If none, returns {-1, -1}
// Tested Timus 1469, CF 1359F
namespace IntersectingSegments {
    struct Event {
        Tf x;
        int tp, id;
        bool operator < (const Event &p) const {
            if (dcmp(x - p.x)) return x < p.x;
            return tp > p.tp;
        }
    };

    pair<int, int> anyIntersection(const vector<Segment> &v) {
        using Linear::segmentsIntersect;
        static_assert(is_same<Tf, Ti>::value);

        vector<Event> ev;
        for (int i=0; i<v.size(); i++) {
            ev.push_back({min(v[i].a.x, v[i].b.x), +1, i});
            ev.push_back({max(v[i].a.x, v[i].b.x), -1, i});
        }
        sort(ev.begin(), ev.end());

        auto comp = [&v] (int i, int j) {
            Segment p = v[i], q = v[j];
            Tf x = max(min(p.a.x, p.b.x), min(q.a.x, q.b.x));
            auto yvalSegment = [&x](const Line &s) {
                if (dcmp(s.a.x - s.b.x) == 0) return s.a.y;
                return s.a.y + (s.b.y - s.a.y) * (x - s.a.x) / (s.b.x - s.a.x);
            };
            return dcmp(yvalSegment(p) - yvalSegment(q)) < 0;
        };

        multiset<int, decltype(comp)> st(comp);
        typedef decltype(st)::iterator iter;
        auto prev = [&st](iter it) {
            return it == st.begin() ? st.end() : --it;
        };
        auto next = [&st](iter it) {
            return it == st.end() ? st.end() : ++it;
        };

        vector<iter> pos(v.size());
        for (auto &cur : ev) {
            int id = cur.id;
            if (cur.tp == 1) {
                iter nxt = st.lower_bound(id);
                iter pre = prev(nxt);
                if (pre != st.end() && segmentsIntersect(v[*pre], v[id]))   return {*pre, id};
                if (nxt != st.end() && segmentsIntersect(v[*nxt], v[id]))   return {*nxt, id};
                pos[id] = st.insert(nxt, id);
            }
            else {
                iter nxt = next(pos[id]);
                iter pre = prev(pos[id]);
                if (pre != st.end() && nxt != st.end() && segmentsIntersect(v[*pre], v[*nxt]))
                    return {*pre, *nxt};
                st.erase(pos[id]);
            }
        }
        return {-1, -1};
    }
}
namespace HalfPlanar {
    using Linear::lineLineIntersection;

    struct DirLine {
        Point p, v;
        Tf ang;
        DirLine() {}
        /// Directed line containing point P in the direction v
        DirLine(Point p, Point v) : p(p), v(v) { ang = atan2(v.y, v.x); }
        /// Directed Line for ax+by+c >=0
        DirLine(Tf a, Tf b, Tf c) {
            assert(dcmp(a) || dcmp(b));
            p = dcmp(a) ? Point(-c/a, 0) : Point(0,-c/b);
            v = Point(b, -a);
            ang = atan2(v.y, v.x);
        }
        bool operator<(const DirLine& u) const { return ang < u.ang; }
        bool onLeft(Point x) const { return dcmp(cross(v, x-p)) >= 0; }
    };

    // Returns the region bounded by the left side of some directed lines
    // MAY CONTAIN DUPLICATE POINTS
    // OUTPUT IS UNDEFINED if intersection is unbounded
    // Complexity: O(n log n) for sorting, O(n) afterwards
    Polygon halfPlaneIntersection(vector<DirLine> li) {
        int n = li.size(), first = 0, last = 0;
        sort(li.begin(), li.end());
        vector<Point> p(n);
        vector<DirLine> q(n);
        q[0] = li[0];

        for (int i = 1; i < n; i++) {
            while (first < last && !li[i].onLeft(p[last - 1])) last--;
            while (first < last && !li[i].onLeft(p[first])) first++;
            q[++last] = li[i];
            if (dcmp(cross(q[last].v, q[last-1].v)) == 0) {
                last--;
                if (q[last].onLeft(li[i].p)) q[last] = li[i];
            }
            if (first < last)
                lineLineIntersection(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v, p[last - 1]);
        }

        while (first < last && !q[first].onLeft(p[last - 1])) last--;
        if (last - first <= 1) return {};
        lineLineIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);
        return Polygon(p.begin()+first, p.begin()+last+1);
    }

    // O(n^2 lg n) implementation of Voronoi Diagram bounded by INF square
    // returns region, where regions[i] = set of points for which closest
    // point is site[i]. This region is a polygon.
    const Tf INF = 1e10;
    vector<Polygon> voronoi(const vector<Point> &site, Tf bsq) {
        int n = site.size();
        vector<Polygon> region(n);
        Point A(-bsq, -bsq), B(bsq, -bsq), C(bsq, bsq), D(-bsq, bsq);

        for (int i = 0; i < n; ++i) {
            vector<DirLine> li(n - 1);
            for (int j = 0, k = 0; j < n; ++j) {
                if (i == j) continue;
                li[k++] = DirLine((site[i] + site[j]) >> 1, rotate90(site[j] - site[i]));
            }
            li.emplace_back(A, B - A);
            li.emplace_back(B, C - B);
            li.emplace_back(C, D - C);
            li.emplace_back(D, A - D);
            region[i] = halfPlaneIntersection(li);
        }
        return region;
    }
}

namespace PointRotationTrick {
    /// you may define the processor function in this namespace
    /// instead of passing as an argument; testing shows function
    /// defined using lambda and passed as argument performs better
    /// tested on:
    /// constant width strip - https://codeforces.com/gym/100016/problem/I
    /// constant area triangle - https://codeforces.com/contest/1019/problem/D
    /// smallest area quadrilateral - https://codingcompetitions.withgoogle.com/codejamio/round/000000000019ff03/00000000001b5e89
    /// disjoint triangles count - https://codeforces.com/contest/1025/problem/F
    /// smallest and largest triangle - http://serjudging.vanb.org/?p=561
    typedef pair< int , int >PII;
    void performTrick(vector< Point >pts, const function<void(const vector< Point >&, int)> &processor) {
        int n = pts.size();
        sort(pts.begin(), pts.end());
        vector< int >position(n);
        vector< PII >segments;
        segments.reserve((n*(n-1))/2);
        for (int i = 0; i < n; i++) {
            position[i] = i;
            for (int j = i+1; j < n; j++) {
                segments.emplace_back(i, j);
            }
        }
        assert(segments.capacity() == segments.size());
        sort(segments.begin(), segments.end(), [&](PII p, PII q) {
            Ti prod = cross(pts[p.second]-pts[p.first], pts[q.second]-pts[q.first]);
            if (prod != 0) return prod > 0;
            return p < q;
        });
        for (PII seg : segments) {
            int i = position[seg.first];
            assert(position[seg.second] == i+1);
            processor(pts, i);
            swap(pts[i], pts[i+1]);
            swap(position[seg.first], position[seg.second]);
        }
    }
}

                                // OR,

#include<bits/stdc++.h>
using namespace std;

// https://victorlecomte.com/cp-geo.pdf
const int N = 3e5 + 9;

const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
struct PT {
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r) { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
istream &operator >> (istream &in, PT &p) { return in >> p.x >> p.y; }
ostream &operator << (ostream &out, PT &p) { return out << "(" << p.x << "," << p.y << ")"; }
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
double SQ(double x) { return x * x; }
double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }
double get_angle(PT a, PT b) {
    double costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((double)-1.0, min((double)1.0, costheta)));
}
bool is_point_in_angle(PT b, PT a, PT c, PT p) { // does point p lie in angle <bac
    assert(orientation(a, b, c) != 0);
    if (orientation(a, c, b) < 0) swap(b, c);
    return orientation(a, c, p) >= 0 && orientation(a, b, p) <= 0;
}
bool half(PT p) {
    return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0);
}
void polar_sort(vector<PT> &v) { // sort points in counterclockwise
    sort(v.begin(), v.end(), [](PT a,PT b) {
        return make_tuple(half(a), 0.0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2());
    });
}
void polar_sort(vector<PT> &v, PT o) { // sort points in counterclockwise with respect to point o
    sort(v.begin(), v.end(), [&](PT a,PT b) {
        return make_tuple(half(a - o), 0.0, (a - o).norm2()) < make_tuple(half(b - o), cross(a - o, b - o), (b - o).norm2());
    });
}
struct line {
    PT a, b; // goes through points a and b
    PT v; double c;  //line form: direction vec [cross] (x, y) = c
    line() {}
    //direction vector v and offset c
	line(PT v, double c) : v(v), c(c) {
        auto p = get_points();
        a = p.first; b = p.second;
	}
	// equation ax + by + c = 0
	line(double _a, double _b, double _c) : v({_b, -_a}), c(-_c) {
		auto p = get_points();
        a = p.first; b = p.second;
	}
	// goes through points p and q
	line(PT p, PT q) : v(q - p), c(cross(v, p)), a(p), b(q) {}
    	pair<PT, PT> get_points() { //extract any two points from this line
		PT p, q; double a = -v.y, b = v.x; // ax + by = c
		if (sign(a) == 0) {
		    p = PT(0, c / b);
		    q = PT(1, c / b);
		}
		else if (sign(b) == 0) {
		    p = PT(c / a, 0);
		    q = PT(c / a, 1);
		}
		else {
		    p = PT(0, c / b);
		    q = PT(1, (c - a) / b);
		}
		return {p, q};
    	}
    // ax + by + c = 0
    array<double, 3> get_abc() {
        double a = -v.y, b = v.x;
        return {a, b, -c};
    }
    // 1 if on the left, -1 if on the right, 0 if on the line
    int side(PT p) { return sign(cross(v, p) - c); }
    // line that is perpendicular to this and goes through point p
    line perpendicular_through(PT p) { return {p, p + perp(v)}; }
    // translate the line by vector t i.e. shifting it by vector t
    line translate(PT t) { return {v, c + cross(v, t)}; }
    // compare two points by their orthogonal projection on this line
    // a projection point comes before another if it comes first according to vector v
    bool cmp_by_projection(PT p, PT q) { return dot(v, p) < dot(v, q); }
	line shift_left(double d) {
		PT z = v.perp().truncate(d);
		return line(a + z, b + z);
	}
};
// find a point from a through b with distance d
PT point_along_line(PT a, PT b, double d) {
    assert(a != b);
    return a + (((b - a) / (b - a).norm()) * d);
}
// projection point c onto line through a and b  assuming a != b
PT project_from_point_to_line(PT a, PT b, PT c) {
    return a + (b - a) * dot(c - a, b - a) / (b - a).norm2();
}
// reflection point c onto line through a and b  assuming a != b
PT reflection_from_point_to_line(PT a, PT b, PT c) {
    PT p = project_from_point_to_line(a,b,c);
    return p + p - c;
}
// minimum distance from point c to line through a and b
double dist_from_point_to_line(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) / (b - a).norm());
}
// returns true if  point p is on line segment ab
bool is_point_on_seg(PT a, PT b, PT p) {
    if (fabs(cross(p - b, a - b)) < eps) {
        if (p.x < min(a.x, b.x) - eps || p.x > max(a.x, b.x) + eps) return false;
        if (p.y < min(a.y, b.y) - eps || p.y > max(a.y, b.y) + eps) return false;
        return true;
    }
    return false;
}
// minimum distance point from point c to segment ab that lies on segment ab
PT project_from_point_to_seg(PT a, PT b, PT c) {
    double r = dist2(a, b);
    if (sign(r) == 0) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}
// minimum distance from point c to segment ab
double dist_from_point_to_seg(PT a, PT b, PT c) {
    return dist(c, project_from_point_to_seg(a, b, c));
}
// 0 if not parallel, 1 if parallel, 2 if collinear
int is_parallel(PT a, PT b, PT c, PT d) {
    double k = fabs(cross(b - a, d - c));
    if (k < eps){
        if (fabs(cross(a - b, a - c)) < eps && fabs(cross(c - d, c - a)) < eps) return 2;
        else return 1;
    }
    else return 0;
}
// check if two lines are same
bool are_lines_same(PT a, PT b, PT c, PT d) {
    if (fabs(cross(a - c, c - d)) < eps && fabs(cross(b - c, c - d)) < eps) return true;
    return false;
}
// bisector vector of <abc
PT angle_bisector(PT &a, PT &b, PT &c){
    PT p = a - b, q = c - b;
    return p + q * sqrt(dot(p, p) / dot(q, q));
}
// 1 if point is ccw to the line, 2 if point is cw to the line, 3 if point is on the line
int point_line_relation(PT a, PT b, PT p) {
    int c = sign(cross(p - a, b - a));
    if (c < 0) return 1;
    if (c > 0) return 2;
    return 3;
}
// intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}
// intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    double oa = cross2(c, d, a), ob = cross2(c, d, b);
    double oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0){
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}
// intersection point between segment ab and segment cd assuming unique intersection may not exists
// se.size()==0 means no intersection
// se.size()==1 means one intersection
// se.size()==2 means range intersection
set<PT> seg_seg_intersection_inside(PT a,  PT b,  PT c,  PT d) {
    PT ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<PT> se;
    if (is_point_on_seg(c, d, a)) se.insert(a);
    if (is_point_on_seg(c, d, b)) se.insert(b);
    if (is_point_on_seg(a, b, c)) se.insert(c);
    if (is_point_on_seg(a, b, d)) se.insert(d);
    return se;
}
// intersection  between segment ab and line cd
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect
int seg_line_relation(PT a, PT b, PT c, PT d) {
    double p = cross2(c, d, a);
    double q = cross2(c, d, b);
    if (sign(p) == 0 && sign(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}
// intersection between segament ab and line cd assuming unique intersection exists
bool seg_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    bool k = seg_line_relation(a, b, c, d);
    assert(k != 2);
    if (k) line_line_intersection(a, b, c, d, ans);
    return k;
}
// minimum distance from segment ab to segment cd
double dist_from_seg_to_seg(PT a, PT b, PT c, PT d) {
    PT dummy;
    if (seg_seg_intersection(a, b, c, d, dummy)) return 0.0;
    else return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d),
        dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
// minimum distance from point c to ray (starting point a and direction vector b)
double dist_from_point_to_ray(PT a, PT b, PT c) {
    b = a + b;
    double r = dot(c - a, b - a);
    if (r < 0.0) return dist(c, a);
    return dist_from_point_to_line(a, b, c);
}
// starting point as and direction vector ad
bool ray_ray_intersection(PT as, PT ad, PT bs, PT bd) {
    double dx = bs.x - as.x, dy = bs.y - as.y;
    double det = bd.x * ad.y - bd.y * ad.x;
    if (fabs(det) < eps) return 0;
    double u = (dy * bd.x - dx * bd.y) / det;
    double v = (dy * ad.x - dx * ad.y) / det;
    if (sign(u) >= 0 && sign(v) >= 0) return 1;
    else return 0;
}
double ray_ray_distance(PT as, PT ad, PT bs, PT bd) {
    if (ray_ray_intersection(as, ad, bs, bd)) return 0.0;
    double ans = dist_from_point_to_ray(as, ad, bs);
    ans = min(ans, dist_from_point_to_ray(bs, bd, as));
    return ans;
}
struct circle {
    PT p; double r;
    circle() {}
    circle(PT _p, double _r): p(_p), r(_r) {};
    // center (x, y) and radius r
    circle(double x, double y, double _r): p(PT(x, y)), r(_r) {};
    // circumcircle of a triangle
    // the three points must be unique
    circle(PT a, PT b, PT c) {
        b = (a + b) * 0.5;
        c = (a + c) * 0.5;
        line_line_intersection(b, b + rotatecw90(a - b), c, c + rotatecw90(a - c), p);
        r = dist(a, p);
    }
    // inscribed circle of a triangle
    // pass a bool just to differentiate from circumcircle
    circle(PT a, PT b, PT c, bool t) {
        line u, v;
        double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
        u.a = a;
        u.b = u.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
        v.a = b;
        m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
        v.b = v.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
        line_line_intersection(u.a, u.b, v.a, v.b, p);
        r = dist_from_point_to_seg(a, b, p);
    }
    bool operator == (circle v) { return p == v.p && sign(r - v.r) == 0; }
    double area() { return PI * r * r; }
    double circumference() { return 2.0 * PI * r; }
};
//0 if outside, 1 if on circumference, 2 if inside circle
int circle_point_relation(PT p, double r, PT b) {
    double d = dist(p, b);
    if (sign(d - r) < 0) return 2;
    if (sign(d - r) == 0) return 1;
    return 0;
}
// 0 if outside, 1 if on circumference, 2 if inside circle
int circle_line_relation(PT p, double r, PT a, PT b) {
    double d = dist_from_point_to_line(a, b, p);
    if (sign(d - r) < 0) return 2;
    if (sign(d - r) == 0) return 1;
    return 0;
}
//compute intersection of line through points a and b with
//circle centered at c with radius r > 0
vector<PT> circle_line_intersection(PT c, double r, PT a, PT b) {
    vector<PT> ret;
    b = b - a; a = a - c;
    double A = dot(b, b), B = dot(a, b);
    double C = dot(a, a) - r * r, D = B * B - A * C;
    if (D < -eps) return ret;
    ret.push_back(c + a + b * (-B + sqrt(D + eps)) / A);
    if (D > eps) ret.push_back(c + a + b * (-B - sqrt(D)) / A);
    return ret;
}
//5 - outside and do not intersect
//4 - intersect outside in one point
//3 - intersect in 2 points
//2 - intersect inside in one point
//1 - inside and do not intersect
int circle_circle_relation(PT a, double r, PT b, double R) {
    double d = dist(a, b);
    if (sign(d - r - R) > 0)  return 5;
    if (sign(d - r - R) == 0) return 4;
    double l = fabs(r - R);
    if (sign(d - r - R) < 0 && sign(d - l) > 0) return 3;
    if (sign(d - l) == 0) return 2;
    if (sign(d - l) < 0) return 1;
    assert(0); return -1;
}
vector<PT> circle_circle_intersection(PT a, double r, PT b, double R) {
    if (a == b && sign(r - R) == 0) return {PT(1e18, 1e18)};
    vector<PT> ret;
    double d = sqrt(dist2(a,  b));
    if (d > r + R || d + min(r,  R) < max(r,  R)) return ret;
    double x = (d * d - R * R + r * r) / (2 * d);
    double y = sqrt(r * r - x * x);
    PT v = (b - a) / d;
    ret.push_back(a + v * x  +  rotateccw90(v) * y);
    if (y > 0) ret.push_back(a + v * x - rotateccw90(v) * y);
    return ret;
}
// returns two circle c1, c2 through points a, b and of radius r
// 0 if there is no such circle, 1 if one circle, 2 if two circle
int get_circle(PT a, PT b, double r, circle &c1, circle &c2) {
    vector<PT> v = circle_circle_intersection(a, r, b, r);
    int t = v.size();
    if (!t) return 0;
    c1.p = v[0], c1.r = r;
    if (t == 2) c2.p = v[1], c2.r = r;
    return t;
}
// returns two circle c1, c2 which is tangent to line u,  goes through
// point q and has radius r1; 0 for no circle, 1 if c1 = c2 , 2 if c1 != c2
int get_circle(line u, PT q, double r1, circle &c1, circle &c2) {
    double d = dist_from_point_to_line(u.a, u.b, q);
    if (sign(d - r1 * 2.0) > 0) return 0;
    if (sign(d) == 0) {
    	cout << u.v.x << ' ' << u.v.y << '\n';
        c1.p = q + rotateccw90(u.v).truncate(r1);
        c2.p = q + rotatecw90(u.v).truncate(r1);
        c1.r = c2.r = r1;
        return 2;
    }
    line u1 = line(u.a + rotateccw90(u.v).truncate(r1), u.b + rotateccw90(u.v).truncate(r1));
    line u2 = line(u.a + rotatecw90(u.v).truncate(r1), u.b + rotatecw90(u.v).truncate(r1));
    circle cc = circle(q, r1);
    PT p1, p2; vector<PT> v;
    v = circle_line_intersection(q, r1, u1.a, u1.b);
    if (!v.size()) v = circle_line_intersection(q, r1, u2.a, u2.b);
    v.push_back(v[0]);
    p1 = v[0], p2 = v[1];
    c1 = circle(p1, r1);
    if (p1 == p2) {
        c2 = c1;
        return 1;
    }
    c2 = circle(p2, r1);
    return 2;
}
// returns the circle such that for all points w on the circumference of the circle
// dist(w, a) : dist(w, b) = rp : rq
// rp != rq
// https://en.wikipedia.org/wiki/Circles_of_Apollonius
circle get_apollonius_circle(PT p, PT q, double rp, double rq ){
    rq *= rq ;
    rp *= rp ;
    double a = rq - rp ;
    assert(sign(a));
    double g = rq * p.x - rp * q.x ; g /= a ;
    double h = rq * p.y - rp * q.y ; h /= a ;
    double c = rq * p.x * p.x - rp * q.x * q.x + rq * p.y * p.y - rp * q.y * q.y ;
    c /= a ;
    PT o(g, h);
    double r = g * g + h * h - c ;
    r = sqrt(r);
    return circle(o,r);
}
// returns area of intersection between two circles
double circle_circle_area(PT a, double r1, PT b, double r2) {
    double d = (a - b).norm();
    if(r1 + r2 < d + eps) return 0;
    if(r1 + d < r2 + eps) return PI * r1 * r1;
    if(r2 + d < r1 + eps) return PI * r2 * r2;
    double theta_1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d)),
    	theta_2 = acos((r2 * r2 + d * d - r1 * r1)/(2 * r2 * d));
    return r1 * r1 * (theta_1 - sin(2 * theta_1)/2.) + r2 * r2 * (theta_2 - sin(2 * theta_2)/2.);
}
// tangent lines from point q to the circle
int tangent_lines_from_point(PT p, double r, PT q, line &u, line &v) {
    int x = sign(dist2(p, q) - r * r);
    if (x < 0) return 0; // point in cricle
    if (x == 0) { // point on circle
        u = line(q, q + rotateccw90(q - p));
        v = u;
        return 1;
    }
    double d = dist(p, q);
    double l = r * r / d;
    double h = sqrt(r * r - l * l);
    u = line(q, p + ((q - p).truncate(l) + (rotateccw90(q - p).truncate(h))));
    v = line(q, p + ((q - p).truncate(l) + (rotatecw90(q - p).truncate(h))));
    return 2;
}
// returns outer tangents line of two circles
// if inner == 1 it returns inner tangent lines
int tangents_lines_from_circle(PT c1, double r1, PT c2, double r2, bool inner, line &u, line &v) {
    if (inner) r2 = -r2;
    PT d = c2 - c1;
    double dr = r1 - r2, d2 = d.norm2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    vector<pair<PT, PT>>out;
    for (int tmp: {- 1, 1}) {
        PT v = (d * dr + rotateccw90(d) * sqrt(h2) * tmp) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    u = line(out[0].first, out[0].second);
    if (out.size() == 2) v = line(out[1].first, out[1].second);
    return 1 + (h2 > 0);
}
// O(n^2 log n)
// https://vjudge.net/problem/UVA-12056
struct CircleUnion {
    int n;
    double x[2020], y[2020], r[2020];
    int covered[2020];
    vector<pair<double, double> > seg, cover;
    double arc, pol;
    inline int sign(double x) {return x < -eps ? -1 : x > eps;}
    inline int sign(double x, double y) {return sign(x - y);}
    inline double SQ(const double x) {return x * x;}
    inline double dist(double x1, double y1, double x2, double y2) {return sqrt(SQ(x1 - x2) + SQ(y1 - y2));}
    inline double angle(double A, double B, double C) {
        double val = (SQ(A) + SQ(B) - SQ(C)) / (2 * A * B);
        if (val < -1) val = -1;
        if (val > +1) val = +1;
        return acos(val);
    }
    CircleUnion() {
        n = 0;
        seg.clear(), cover.clear();
        arc = pol = 0;
    }
    void init() {
        n = 0;
        seg.clear(), cover.clear();
        arc = pol = 0;
    }
    void add(double xx, double yy, double rr) {
        x[n] = xx, y[n] = yy, r[n] = rr, covered[n] = 0, n++;
    }
    void getarea(int i, double lef, double rig) {
        arc += 0.5 * r[i] * r[i] * (rig - lef - sin(rig - lef));
        double x1 = x[i] + r[i] * cos(lef), y1 = y[i] + r[i] * sin(lef);
        double x2 = x[i] + r[i] * cos(rig), y2 = y[i] + r[i] * sin(rig);
        pol += x1 * y2 - x2 * y1;
    }
    double solve() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (!sign(x[i] - x[j]) && !sign(y[i] - y[j]) && !sign(r[i] - r[j])) {
                    r[i] = 0.0;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && sign(r[j] - r[i]) >= 0 && sign(dist(x[i], y[i], x[j], y[j]) - (r[j] - r[i])) <= 0) {
                    covered[i] = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (sign(r[i]) && !covered[i]) {
                seg.clear();
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        double d = dist(x[i], y[i], x[j], y[j]);
                        if (sign(d - (r[j] + r[i])) >= 0 || sign(d - abs(r[j] - r[i])) <= 0) {
                            continue;
                        }
                        double alpha = atan2(y[j] - y[i], x[j] - x[i]);
                        double beta = angle(r[i], d, r[j]);
                        pair<double, double> tmp(alpha - beta, alpha + beta);
                        if (sign(tmp.first) <= 0 && sign(tmp.second) <= 0) {
                            seg.push_back(pair<double, double>(2 * PI + tmp.first, 2 * PI + tmp.second));
                        }
                        else if (sign(tmp.first) < 0) {
                            seg.push_back(pair<double, double>(2 * PI + tmp.first, 2 * PI));
                            seg.push_back(pair<double, double>(0, tmp.second));
                        }
                        else {
                            seg.push_back(tmp);
                        }
                    }
                }
                sort(seg.begin(), seg.end());
                double rig = 0;
                for (vector<pair<double, double> >::iterator iter = seg.begin(); iter != seg.end(); iter++) {
                    if (sign(rig - iter->first) >= 0) {
                        rig = max(rig, iter->second);
                    }
                    else {
                        getarea(i, rig, iter->first);
                        rig = iter->second;
                    }
                }
                if (!sign(rig)) {
                    arc += r[i] * r[i] * PI;
                }
                else {
                    getarea(i, rig, 2 * PI);
                }
            }
        }
        return pol / 2.0 + arc;
    }
} CU;
double area_of_triangle(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) * 0.5);
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_triangle(PT a, PT b, PT c, PT p) {
    if (sign(cross(b - a,c - a)) < 0) swap(b, c);
    int c1 = sign(cross(b - a,p - a));
    int c2 = sign(cross(c - b,p - b));
    int c3 = sign(cross(a - c,p - c));
    if (c1<0 || c2<0 || c3 < 0) return 1;
    if (c1 + c2 + c3 != 3) return 0;
    return -1;
}
double perimeter(vector<PT> &p) {
    double ans=0; int n = p.size();
    for (int i = 0; i < n; i++) ans += dist(p[i], p[(i + 1) % n]);
    return ans;
}
double area(vector<PT> &p) {
    double ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    return fabs(ans) * 0.5;
}
// centroid of a (possibly non-convex) polygon,
// assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
PT centroid(vector<PT> &p) {
    int n = p.size(); PT c(0, 0);
    double sum = 0;
    for (int i = 0; i < n; i++) sum += cross(p[i], p[(i + 1) % n]);
    double scale = 3.0 * sum;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        c = c + (p[i] + p[j]) * cross(p[i], p[j]);
    }
    return c / scale;
}
// 0 if cw, 1 if ccw
bool get_direction(vector<PT> &p) {
    double ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    if (sign(ans) > 0) return 1;
    return 0;
}
// it returns a point such that the sum of distances
// from that point to all points in p  is minimum
// O(n log^2 MX)
PT geometric_median(vector<PT> p) {
	auto tot_dist = [&](PT z) {
	    double res = 0;
	    for (int i = 0; i < p.size(); i++) res += dist(p[i], z);
	    return res;
	};
	auto findY = [&](double x) {
	    double yl = -1e5, yr = 1e5;
	    for (int i = 0; i < 60; i++) {
	        double ym1 = yl + (yr - yl) / 3;
	        double ym2 = yr - (yr - yl) / 3;
	        double d1 = tot_dist(PT(x, ym1));
	        double d2 = tot_dist(PT(x, ym2));
	        if (d1 < d2) yr = ym2;
	        else yl = ym1;
	    }
	    return pair<double, double> (yl, tot_dist(PT(x, yl)));
	};
    double xl = -1e5, xr = 1e5;
    for (int i = 0; i < 60; i++) {
        double xm1 = xl + (xr - xl) / 3;
        double xm2 = xr - (xr - xl) / 3;
        double y1, d1, y2, d2;
        auto z = findY(xm1); y1 = z.first; d1 = z.second;
        z = findY(xm2); y2 = z.first; d2 = z.second;
        if (d1 < d2) xr = xm2;
        else xl = xm1;
    }
    return {xl, findY(xl).first };
}
vector<PT> convex_hull(vector<PT> &p) {
	if (p.size() <= 1) return p;
	vector<PT> v = p;
    sort(v.begin(), v.end());
    vector<PT> up, dn;
    for (auto& p : v) {
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0) {
            dn.pop_back();
        }
        up.push_back(p);
        dn.push_back(p);
    }
    v = dn;
    if (v.size() > 1) v.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (auto& p : up) {
        v.push_back(p);
    }
    if (v.size() == 2 && v[0] == v[1]) v.pop_back();
    return v;
}
 //checks if convex or not
bool is_convex(vector<PT> &p) {
    bool s[3]; s[0] = s[1] = s[2] = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        s[sign(cross(p[j] - p[i], p[k] - p[i])) + 1] = 1;
        if (s[0] && s[2]) return 0;
    }
    return 1;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int is_point_in_convex(vector<PT> &p, const PT& x) { // O(log n)
    int n = p.size(); assert(n >= 3);
    int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (orientation(p[0], p[mid], x) >= 0) l = mid;
        else r = mid;
    }
    int k = orientation(p[l], p[r], x);
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}
bool is_point_on_polygon(vector<PT> &p, const PT& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
    	if (is_point_on_seg(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}
// returns 1e9 if the point is on the polygon
int winding_number(vector<PT> &p, const PT& z) { // O(n)
    if (is_point_on_polygon(p, z)) return 1e9;
    int n = p.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        bool below = p[i].y < z.y;
        if (below != (p[j].y < z.y)) {
            auto orient = orientation(z, p[j], p[i]);
            if (orient == 0) return 0;
            if (below == (orient > 0)) ans += below ? 1 : -1;
        }
    }
    return ans;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<PT> &p, const PT& z) { // O(n)
    int k = winding_number(p, z);
    return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}
// id of the vertex having maximum dot product with z
// polygon must need to be convex
// top - upper right vertex
// for minimum dot product negate z and return -dot(z, p[id])
int extreme_vertex(vector<PT> &p, const PT &z, const int top) { // O(log n)
    int n = p.size();
    if (n == 1) return 0;
	double ans = dot(p[0], z); int id = 0;
    if (dot(p[top], z) > ans) ans = dot(p[top], z), id = top;
    int l = 1, r = top - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (dot(p[mid + 1], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
    l = top + 1, r = n - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (dot(p[(mid + 1) % n], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    l %= n;
    if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
    return id;
}
// maximum distance from any point on the perimeter to another point on the perimeter
double diameter(vector<PT> &p) {
    int n = (int)p.size();
    if (n == 1) return 0;
    if (n == 2) return dist(p[0], p[1]);
    double ans = 0;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) {
        	ans = max(ans, dist2(p[i], p[j]));
        	j = (j + 1) % n;
        }
        ans = max(ans, dist2(p[i], p[j]));
        i++;
    }
    return sqrt(ans);
}
// minimum distance between two parallel lines (non necessarily axis parallel)
// such that the polygon can be put between the lines
double width(vector<PT> &p) {
    int n = (int)p.size();
    if (n <= 2) return 0;
    double ans = inf;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        ans = min(ans, dist_from_point_to_line(p[i], p[(i + 1) % n], p[j]));
        i++;
    }
    return ans;
}
// minimum perimeter
double minimum_enclosing_rectangle(vector<PT> &p) {
	int n = p.size();
	if (n <= 2) return perimeter(p);
	int mndot = 0; double tmp = dot(p[1] - p[0], p[0]);
	for (int i = 1; i < n; i++) {
		if (dot(p[1] - p[0], p[i]) <= tmp) {
			tmp = dot(p[1] - p[0], p[i]);
			mndot = i;
		}
	}
	double ans = inf;
	int i = 0, j = 1, mxdot = 1;
	while (i < n) {
		PT cur = p[(i + 1) % n] - p[i];
        while (cross(cur, p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        while (dot(p[(mxdot + 1) % n], cur) >= dot(p[mxdot], cur)) mxdot = (mxdot + 1) % n;
        while (dot(p[(mndot + 1) % n], cur) <= dot(p[mndot], cur)) mndot = (mndot + 1) % n;
        ans = min(ans, 2.0 * ((dot(p[mxdot], cur) / cur.norm() - dot(p[mndot], cur) / cur.norm()) + dist_from_point_to_line(p[i], p[(i + 1) % n], p[j])));
        i++;
    }
    return ans;
}
// given n points, find the minimum enclosing circle of the points
// call convex_hull() before this for faster solution
// expected O(n)
circle minimum_enclosing_circle(vector<PT> &p) {
    random_shuffle(p.begin(), p.end());
    int n = p.size();
    circle c(p[0], 0);
    for (int i = 1; i < n; i++) {
        if (sign(dist(c.p, p[i]) - c.r) > 0) {
            c = circle(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (sign(dist(c.p, p[j]) - c.r) > 0) {
                    c = circle((p[i] + p[j]) / 2, dist(p[i], p[j]) / 2);
                    for (int k = 0; k < j; k++) {
                        if (sign(dist(c.p, p[k]) - c.r) > 0) {
                            c = circle(p[i], p[j], p[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}
// returns a vector with the vertices of a polygon with everything
// to the left of the line going from a to b cut away.
vector<PT> cut(vector<PT> &p, PT a, PT b) {
    vector<PT> ans;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        double c1 = cross(b - a, p[i] - a);
        double c2 = cross(b - a, p[(i + 1) % n] - a);
        if (sign(c1) >= 0) ans.push_back(p[i]);
        if (sign(c1 * c2) < 0) {
            if (!is_parallel(p[i], p[(i + 1) % n], a, b)) {
            	PT tmp; line_line_intersection(p[i], p[(i + 1) % n], a, b, tmp);
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}
// not necessarily convex, boundary is included in the intersection
// returns total intersected length
// it returns the sum of the lengths of the portions of the line that are inside the polygon
double polygon_line_intersection(vector<PT> p, PT a, PT b) {
    int n = p.size();
    p.push_back(p[0]);
    line l = line(a, b);
    double ans = 0.0;
    vector< pair<double, int> > vec;
    for (int i = 0; i < n; i++) {
        int s1 = orientation(a, b, p[i]);
        int s2 = orientation(a, b, p[i + 1]);
        if (s1 == s2) continue;
        line t = line(p[i], p[i + 1]);
        PT inter = (t.v * l.c - l.v * t.c) / cross(l.v, t.v);
        double tmp = dot(inter, l.v);
        int f;
        if (s1 > s2) f = s1 && s2 ? 2 : 1;
        else f = s1 && s2 ? -2 : -1;
        vec.push_back(make_pair((f > 0 ? tmp - eps : tmp + eps), f)); // keep eps very small like 1e-12
    }
    sort(vec.begin(), vec.end());
    for (int i = 0, j = 0; i + 1 < (int)vec.size(); i++){
        j += vec[i].second;
        if (j) ans += vec[i + 1].first - vec[i].first; // if this portion is inside the polygon
        // else ans = 0; // if we want the maximum intersected length which is totally inside the polygon, uncomment this and take the maximum of ans
    }
    ans = ans / sqrt(dot(l.v, l.v));
    p.pop_back();
    return ans;
}
// given a convex polygon p, and a line ab and the top vertex of the polygon
// returns the intersection of the line with the polygon
// it returns the indices of the edges of the polygon that are intersected by the line
// so if it returns i, then the line intersects the edge (p[i], p[(i + 1) % n])
array<int, 2> convex_line_intersection(vector<PT> &p, PT a, PT b, int top) {
	int end_a = extreme_vertex(p, (a - b).perp(), top);
    int end_b = extreme_vertex(p, (b - a).perp(), top);
    auto cmp_l = [&](int i) { return orientation(a, p[i], b); };
    if (cmp_l(end_a) < 0 || cmp_l(end_b) > 0)
        return {-1, -1}; // no intersection
    array<int, 2> res;
    for (int i = 0; i < 2; i++) {
        int lo = end_b, hi = end_a, n = p.size();
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmp_l(m) == cmp_l(end_b) ? lo : hi) = m;
        }
        res[i] = (lo + !cmp_l(hi)) % n;
        swap(end_a, end_b);
    }
    if (res[0] == res[1]) return {res[0], -1}; // touches the vertex res[0]
    if (!cmp_l(res[0]) && !cmp_l(res[1]))
        switch ((res[0] - res[1] + (int)p.size() + 1) % p.size()) {
            case 0: return {res[0], res[0]}; // touches the edge (res[0], res[0] + 1)
            case 2: return {res[1], res[1]}; // touches the edge (res[1], res[1] + 1)
        }
    return res; // intersects the edges (res[0], res[0] + 1) and (res[1], res[1] + 1)
}

pair<PT, int> point_poly_tangent(vector<PT> &p, PT Q, int dir, int l, int r) {
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        bool pvs = orientation(Q, p[mid], p[mid - 1]) != -dir;
        bool nxt = orientation(Q, p[mid], p[mid + 1]) != -dir;
        if (pvs && nxt) return {p[mid], mid};
        if (!(pvs || nxt)) {
            auto p1 = point_poly_tangent(p, Q, dir, mid + 1, r);
            auto p2 = point_poly_tangent(p, Q, dir, l, mid - 1);
            return orientation(Q, p1.first, p2.first) == dir ? p1 : p2;
        }
        if (!pvs) {
            if (orientation(Q, p[mid], p[l]) == dir)  r = mid - 1;
            else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
            else l = mid + 1;
        }
        if (!nxt) {
            if (orientation(Q, p[mid], p[l]) == dir)  l = mid + 1;
            else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
            else l = mid + 1;
        }
    }
    pair<PT, int> ret = {p[l], l};
    for (int i = l + 1; i <= r; i++) ret = orientation(Q, ret.first, p[i]) != dir ? make_pair(p[i], i) : ret;
    return ret;
}
// (ccw, cw) tangents from a point that is outside this convex polygon
// returns indexes of the points
// ccw means the tangent from Q to that point is in the same direction as the polygon ccw direction
pair<int, int> tangents_from_point_to_polygon(vector<PT> &p, PT Q){
    int ccw = point_poly_tangent(p, Q, 1, 0, (int)p.size() - 1).second;
    int cw = point_poly_tangent(p, Q, -1, 0, (int)p.size() - 1).second;
    return make_pair(ccw, cw);
}

// minimum distance from a point to a convex polygon
// it assumes point lie strictly outside the polygon
double dist_from_point_to_polygon(vector<PT> &p, PT z) {
    double ans = inf;
    int n = p.size();
    if (n <= 3) {
        for(int i = 0; i < n; i++) ans = min(ans, dist_from_point_to_seg(p[i], p[(i + 1) % n], z));
        return ans;
    }
    auto [r, l] = tangents_from_point_to_polygon(p, z);
    if(l > r) r += n;
    while (l < r) {
        int mid = (l + r) >> 1;
        double left = dist2(p[mid % n], z), right= dist2(p[(mid + 1) % n], z);
        ans = min({ans, left, right});
        if(left < right) r = mid;
        else l = mid + 1;
    }
    ans = sqrt(ans);
    ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l + 1) % n], z));
    ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l - 1 + n) % n], z));
    return ans;
}
// minimum distance from convex polygon p to line ab
// returns 0 is it intersects with the polygon
// top - upper right vertex
double dist_from_polygon_to_line(vector<PT> &p, PT a, PT b, int top) { //O(log n)
	PT orth = (b - a).perp();
	if (orientation(a, b, p[0]) > 0) orth = (a - b).perp();
	int id = extreme_vertex(p, orth, top);
	if (dot(p[id] - a, orth) > 0) return 0.0; //if orth and a are in the same half of the line, then poly and line intersects
	return dist_from_point_to_line(a, b, p[id]); //does not intersect
}
// minimum distance from a convex polygon to another convex polygon
// the polygon doesnot overlap or touch
// tested in https://toph.co/p/the-wall
double dist_from_polygon_to_polygon(vector<PT> &p1, vector<PT> &p2) { // O(n log n)
    double ans = inf;
    for (int i = 0; i < p1.size(); i++) {
        ans = min(ans, dist_from_point_to_polygon(p2, p1[i]));
    }
    for (int i = 0; i < p2.size(); i++) {
        ans = min(ans, dist_from_point_to_polygon(p1, p2[i]));
    }
    return ans;
}
// maximum distance from a convex polygon to another convex polygon
double maximum_dist_from_polygon_to_polygon(vector<PT> &u, vector<PT> &v){ //O(n)
    int n = (int)u.size(), m = (int)v.size();
    double ans = 0;
    if (n < 3 || m < 3) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ans = max(ans, dist2(u[i], v[j]));
        }
        return sqrt(ans);
    }
    if (u[0].x > v[0].x) swap(n, m), swap(u, v);
    int i = 0, j = 0, step = n + m + 10;
    while (j + 1 < m && v[j].x < v[j + 1].x) j++ ;
    while (step--) {
        if (cross(u[(i + 1)%n] - u[i], v[(j + 1)%m] - v[j]) >= 0) j = (j + 1) % m;
        else i = (i + 1) % n;
        ans = max(ans, dist2(u[i], v[j]));
    }
    return sqrt(ans);
}

// calculates the area of the union of n polygons (not necessarily convex).
// the points within each polygon must be given in CCW order.
// complexity: O(N^2), where N is the total number of points
double rat(PT a, PT b, PT p) {
        return !sign(a.x - b.x) ? (p.y - a.y) / (b.y - a.y) : (p.x - a.x) / (b.x - a.x);
 };
double polygon_union(vector<vector<PT>> &p) {
	int n = p.size();
    double ans=0;
    for(int i = 0; i < n; ++i) {
        for (int v = 0; v < (int)p[i].size(); ++v) {
            PT a = p[i][v], b = p[i][(v + 1) % p[i].size()];
            vector<pair<double, int>> segs;
            segs.emplace_back(0,  0), segs.emplace_back(1,  0);
            for(int j = 0; j < n; ++j) {
            	if(i != j) {
                    for(size_t u = 0; u < p[j].size(); ++u) {
                        PT c = p[j][u], d = p[j][(u + 1) % p[j].size()];
                        int sc = sign(cross(b - a, c - a)), sd = sign(cross(b - a, d - a));
                        if(!sc && !sd) {
                            if(sign(dot(b - a, d - c)) > 0 && i > j) {
                                segs.emplace_back(rat(a, b, c), 1), segs.emplace_back(rat(a, b, d),  -1);
                            }
                        }
                        else {
                            double sa = cross(d - c, a - c), sb = cross(d - c, b - c);
                            if(sc >= 0 && sd < 0) segs.emplace_back(sa / (sa - sb), 1);
                            else if(sc < 0 && sd >= 0) segs.emplace_back(sa / (sa - sb),  -1);
                        }
                    }
                }
            }
            sort(segs.begin(),  segs.end());
            double pre = min(max(segs[0].first, 0.0), 1.0), now, sum = 0;
            int cnt = segs[0].second;
            for(int j = 1; j < segs.size(); ++j) {
                now = min(max(segs[j].first, 0.0), 1.0);
                if (!cnt) sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ans += cross(a, b) * sum;
        }
    }
    return ans * 0.5;
}
// contains all points p such that: cross(b - a, p - a) >= 0
struct HP {
    PT a, b;
    HP() {}
    HP(PT a, PT b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (const HP& rhs) const {
        PT p = b - a;
        PT q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (cross(p, q)) return cross(p, q) > 0;
        return cross(p, rhs.b - a) < 0;
    }
    PT line_line_intersection(PT a, PT b, PT c, PT d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * cross(c, d) / cross(b, d);
    }
    PT intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};
int check(HP a, HP b, HP c) {
    return cross(a.b - a.a, b.intersection(c) - a.a) > -eps; //-eps to include polygons of zero area (straight lines, points)
}
// consider half-plane of counter-clockwise side of each line
// if lines are not bounded add infinity rectangle
// returns a convex polygon, a point can occur multiple times though
// complexity: O(n log(n))
vector<PT> half_plane_intersection(vector<HP> h) {
    sort(h.begin(), h.end());
    vector<HP> tmp;
    for (int i = 0; i < h.size(); i++) {
        if (!i || cross(h[i].b - h[i].a, h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
    vector<HP> q(h.size() + 10);
    int qh = 0, qe = 0;
    for (int i = 0; i < h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;
    vector<HP> res;
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    vector<PT> hull;
    if (res.size() > 2) {
        for (int i = 0; i < res.size(); i++) {
             hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
        }
    }
    return hull;
}
// rotate the polygon such that the (bottom, left)-most point is at the first position
void reorder_polygon(vector<PT> &p) {
  int pos = 0;
  for (int i = 1; i < p.size(); i++) {
    if (p[i].y < p[pos].y || (sign(p[i].y - p[pos].y) == 0 && p[i].x < p[pos].x)) pos = i;
  }
  rotate(p.begin(), p.begin() + pos, p.end());
}
// a and b are convex polygons
// returns a convex hull of their minkowski sum
// min(a.size(), b.size()) >= 2
// https://cp-algorithms.com/geometry/minkowski.html
vector<PT> minkowski_sum(vector<PT> a, vector<PT> b) {
  reorder_polygon(a); reorder_polygon(b);
  int n = a.size(), m = b.size();
  int i = 0, j = 0;
  a.push_back(a[0]); a.push_back(a[1]);
  b.push_back(b[0]); b.push_back(b[1]);
  vector<PT> c;
  while (i < n || j < m) {
    c.push_back(a[i] + b[j]);
    double p = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
    if (sign(p) >= 0) ++i;
    if (sign(p) <= 0) ++j;
  }
  return c;
}
// returns the area of the intersection of the circle with center c and radius r
// and the triangle formed by the points c, a, b
double _triangle_circle_intersection(PT c, double r, PT a, PT b) {
    double sd1 = dist2(c, a), sd2 = dist2(c, b);
    if(sd1 > sd2) swap(a, b), swap(sd1, sd2);
    double sd = dist2(a, b);
    double d1 = sqrtl(sd1), d2 = sqrtl(sd2), d = sqrt(sd);
    double x = abs(sd2 - sd - sd1) / (2 * d);
    double h = sqrtl(sd1 - x * x);
    if(r >= d2) return h * d / 2;
    double area = 0;
    if(sd + sd1 < sd2) {
        if(r < d1) area = r * r * (acos(h / d2) - acos(h / d1)) / 2;
        else {
            area = r * r * ( acos(h / d2) - acos(h / r)) / 2;
            double y = sqrtl(r * r - h * h);
            area += h * (y - x) / 2;
        }
    }
    else {
        if(r < h) area = r * r * (acos(h / d2) + acos(h / d1)) / 2;
        else {
            area += r * r * (acos(h / d2) - acos(h / r)) / 2;
            double y = sqrtl(r * r - h * h);
            area += h * y / 2;
            if(r < d1) {
                area += r * r * (acos(h / d1) - acos(h / r)) / 2;
                area += h * y / 2;
            }
            else area += h * x / 2;
        }
    }
    return area;
}
// intersection between a simple polygon and a circle
double polygon_circle_intersection(vector<PT> &v, PT p, double r) {
    int n = v.size();
    double ans = 0.00;
    PT org = {0, 0};
    for(int i = 0; i < n; i++) {
        int x = orientation(p, v[i], v[(i + 1) % n]);
        if(x == 0) continue;
        double area = _triangle_circle_intersection(org, r, v[i] - p, v[(i + 1) % n] - p);
        if (x < 0) ans -= area;
        else ans += area;
    }
    return abs(ans);
}
// find a circle of radius r that contains as many points as possible
// O(n^2 log n);
double maximum_circle_cover(vector<PT> p, double r, circle &c) {
    int n = p.size();
    int ans = 0;
    int id = 0; double th = 0;
    for (int i = 0; i < n; ++i) {
        // maximum circle cover when the circle goes through this point
        vector<pair<double, int>> events = {{-PI, +1}, {PI, -1}};
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            double d = dist(p[i], p[j]);
            if (d > r * 2) continue;
            double dir = (p[j] - p[i]).arg();
            double ang = acos(d / 2 / r);
            double st = dir - ang, ed = dir + ang;
            if (st > PI) st -= PI * 2;
            if (st <= -PI) st += PI * 2;
            if (ed > PI) ed -= PI * 2;
            if (ed <= -PI) ed += PI * 2;
            events.push_back({st - eps, +1}); // take care of precisions!
            events.push_back({ed, -1});
            if (st > ed) {
                events.push_back({-PI, +1});
                events.push_back({+PI, -1});
            }
        }
        sort(events.begin(), events.end());
        int cnt = 0;
        for (auto &&e: events) {
            cnt += e.second;
            if (cnt > ans) {
            	ans = cnt;
            	id = i; th = e.first;
            }
        }
    }
    PT w = PT(p[id].x + r * cos(th), p[id].y + r * sin(th));
    c = circle(w, r); //best_circle
    return ans;
}
// radius of the maximum inscribed circle in a convex polygon
double maximum_inscribed_circle(vector<PT> p) {
	int n = p.size();
	if (n <= 2) return 0;
	double l = 0, r = 20000;
	while (r - l > eps) {
		double mid = (l + r) * 0.5;
		vector<HP> h;
		const int L = 1e9;
		h.push_back(HP(PT(-L, -L), PT(L, -L)));
		h.push_back(HP(PT(L, -L), PT(L, L)));
		h.push_back(HP(PT(L, L), PT(-L, L)));
		h.push_back(HP(PT(-L, L), PT(-L, -L)));
		for (int i = 0; i < n; i++) {
			PT z = (p[(i + 1) % n] - p[i]).perp();
			z = z.truncate(mid);
			PT y = p[i] + z, q = p[(i + 1) % n] + z;
			h.push_back(HP(p[i] + z, p[(i + 1) % n] + z));
		}
		vector<PT> nw = half_plane_intersection(h);
		if (!nw.empty()) l = mid;
		else r = mid;
	}
	return l;
}
// ear decomposition, O(n^3) but faster
vector<vector<PT>> triangulate(vector<PT> p) {
  vector<vector<PT>> v;
  while (p.size() >= 3) {
    for (int i = 0, n = p.size(); i < n; i++) {
      int pre = i == 0 ? n - 1 : i - 1;;
      int nxt = i == n - 1 ? 0 : i + 1;;
      int ori = orientation(p[i], p[pre], p[nxt]);
      if (ori < 0) {
        int ok = 1;
        for (int j = 0; j < n; j++) {
          if (j == i || j == pre || j == nxt)continue;
          if (is_point_in_triangle(p[i], p[pre], p[nxt] , p[j]) < 1) {
            ok = 0;
            break;
          }
        }
        if (ok) {
          v.push_back({p[pre], p[i], p[nxt]});
          p.erase(p.begin() + i);
          break;
        }
      }
    }
  }
  return v;
}

struct star {
	int n;    // number of sides of the star
	double r; // radius of the circumcircle
	star(int _n, double _r) {
		n = _n;
		r = _r;
	}

	double area() {
		double theta = PI / n;
		double s = 2 * r * sin(theta);
		double R = 0.5 * s / tan(theta);
		double a = 0.5 * n * s * R;
		double a2 = 0.25 * s * s / tan(1.5 * theta);
		return a - n * a2;
	}
};

// given a list of lengths of the sides of a polygon in counterclockwise order
// returns the maximum area of a non-degenerate polygon that can be formed using those lengths
double get_maximum_polygon_area_for_given_lengths(vector<double> v) {
  if (v.size() < 3) {
    return 0;
  }
  int m = 0;
  double sum = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] > v[m]) {
      m = i;
    }
    sum += v[i];
  }
  if (sign(v[m] - (sum - v[m])) >= 0) {
    return 0; // no non-degenerate polygon is possible
  }
  // the polygon should be a circular polygon
  // that is all points are on the circumference of a circle
  double l = v[m] / 2, r = 1e6; // fix it correctly
  int it = 60;
  auto ang = [](double x, double r) { // x = length of the chord, r = radius of the circle
    return 2 * asin((x / 2) / r);
  };
  auto calc = [=](double r) {
    double sum = 0;
    for (auto x: v) {
      sum += ang(x, r);
    }
    return sum;
  };
  // compute the radius of the circle
  while (it--) {
    double mid = (l + r) / 2;
    if (calc(mid) <= 2 * PI) {
      r = mid;
    }
    else {
      l = mid;
    }
  }

  if (calc(r) <= 2 * PI - eps) { // the center of the circle is outside the polygon
    auto calc2 = [&](double r) {
      double sum = 0;
      for (int i = 0; i < v.size(); i++) {
        double x = v[i];
        double th = ang(x, r);
        if (i != m) {
          sum += th;
        }
        else {
          sum += 2 * PI - th;
        }
      }
      return sum;
    };
    l = v[m] / 2; r = 1e6;
    it = 60;
    while (it--) {
      double mid = (l + r) / 2;
      if (calc2(mid) > 2 * PI) {
        r = mid;
      }
      else {
        l = mid;
      }
    }
    auto get_area = [=](double r) {
      double ans = 0;
      for (int i = 0; i < v.size(); i++) {
        double x = v[i];
        double area = r * r * sin(ang(x, r)) / 2;
        if (i != m) {
          ans += area;
        }
        else {
          ans -= area;
        }
      }
      return ans;
    };
    return get_area(r);
  }
  else { // the center of the circle is inside the polygon
    auto get_area = [=](double r) {
      double ans = 0;
      for (auto x: v) {
        ans += r * r * sin(ang(x, r)) / 2;
      }
      return ans;
    };
    return get_area(r);
  }
}

int32_t main() {
  	ios_base::sync_with_stdio(0);
  	cin.tie(0);

 	return 0;
}

// Geometry 3D:

// #define static_assert(...)

typedef double Tf;
typedef double Ti;  /// use int64_t for exactness
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Point3 {
    Ti x, y, z;
    Point3(Ti x = 0, Ti y = 0, Ti z = 0) : x(x), y(y), z(z) {}

    Point3 operator+(const Point3 &u) const { return Point3(x + u.x, y + u.y, z + u.z); }
    Point3 operator-(const Point3 &u) const { return Point3(x - u.x, y - u.y, z - u.z); }
    Point3 operator*(const int64_t u) const { return Point3(x * u, y * u, z * u); }
    Point3 operator*(const Tf u) const { return Point3(x * u, y * u, z * u); }
    Point3 operator/(const Tf u) const { return Point3(x / u, y / u, z / u); }

    bool operator==(const Point3 &u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z); }
    bool operator!=(const Point3 &u) const { return !(*this == u); }
    bool operator<(const Point3 &u) const {
        return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0) ||
               (dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z) < 0);
    }

    friend istream &operator>>(istream &is, Point3 &p) { return is >> p.x >> p.y >> p.z; }
    friend ostream &operator<<(ostream &os, const Point3 &p) { return os << p.x << " " << p.y << " " << p.z; }
};

Ti dot(Point3 a, Point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Point3 cross(Point3 v, Point3 w) {
    return Point3(v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x);
}

// Tf length(Point3 a) { return sqrt(dot(a, a)); }
// Ti sqLength(Point3 a) { return dot(a, a); }
// Tf distance(Point3 a, Point3 b) {return length(a-b);}
// Tf angle(Point3 u) { return atan2(u.y, u.x); }

// OR,

#include<bits/stdc++.h>
using namespace std;

// https://victorlecomte.com/cp-geo.pdf
const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }

struct PT {
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    void scan() { cin >> x >> y; }
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r) { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
double SQ(double x) { return x * x; }
double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }
double get_angle(PT a, PT b) {
    double costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((double)-1.0, min((double)1.0, costheta)));
}
struct p3 {
    double x, y, z;
    p3() { x = 0, y = 0; z = 0; }
    p3(double x, double y, double z) : x(x), y(y), z(z) {}
    p3(const p3 &p) : x(p.x), y(p.y), z(p.z)    {}
    void scan() { cin >> x >> y >> z; }
    p3 operator + (const p3 &a) const { return p3(x + a.x, y + a.y, z + a.z); }
    p3 operator - (const p3 &a) const { return p3(x - a.x, y - a.y, z - a.z); }
    p3 operator * (const double a) const { return p3(x * a, y * a, z * a); }
    friend p3 operator * (const double &a, const p3 &b) { return p3(a * b.x, a * b.y, a * b.z); }
    p3 operator / (const double a) const { return p3(x / a, y / a, z / a); }
    bool operator == (p3 a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0 && sign(a.z - z) == 0; }
    bool operator != (p3 a) const { return !(*this == a); }
    double abs() { return sqrt(x * x + y * y + z * z); }
    double sq() { return x * x + y * y + z * z; }
    p3 unit() { return *this / abs(); }
}zero(0, 0, 0);
double operator | (p3 v, p3 w) { //dot product
    return v.x * w.x + v.y * w.y + v.z * w.z;
}
p3 operator * (p3 v, p3 w) { //cross product
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x};
}
double sq(p3 v) { return v | v; }
double abs(p3 v) { return sqrt(sq(v)); }
p3 unit(p3 v) { return v / abs(v); }
inline double dot(p3 a, p3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline double dist2(p3 a, p3 b) { return dot(a - b, a - b); }
inline double dist(p3 a, p3 b) { return sqrt(dot(a - b, a - b)); }
inline p3 cross(p3 a, p3 b) { return p3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
// if s is on the same side of the plane pqr as the vector pq * pr then it will be positive
// otherwise negative or 0 if on the plane
double orient(p3 p, p3 q, p3 r, p3 s) { return (q - p) * (r - p) | (s - p); }
// returns orientation of p to q to r on the plane perpendicular to n
// assuming p, q, r are on the plane
double orient_by_normal(p3 p, p3 q, p3 r, p3 n) { return (q - p) * (r - p) | n; }
double get_angle(p3 a, p3 b) {
    double costheta = dot(a, b) / a.abs() / b.abs();
    return acos(max((double)-1.0, min((double)1.0, costheta)));
}
double small_angle(p3 v, p3 w) {
    return acos(min(fabs(v | w) / abs(v) / abs(w), (double)1.0));
}

struct plane {
    // n is the perpendicular normal vector to the plane
    p3 n; double d; // (n | p) = d
    // From normal n and offset d
    plane(p3 n, double d) : n(n), d(d) {}
    // From normal n and point P
    plane(p3 n, p3 p) : n(n), d(n | p) {}
    // From three non-collinear points P,Q,R
    plane(p3 p, p3 q, p3 r) : plane((q - p) * (r - p), p) {}
    // positive if on the same side as the normal, negative if on the opposite side, 0 if on the plane
    double side(p3 p) { return (n | p) - d; }
    // distance from point p to plane
    double dist(p3 p) { return fabs(side(p)) / abs(n); }
    // translate the plane by vector t
    plane translate(p3 t) { return {n, d + (n | t)}; }
    // shift the plane perpendicular to n by distance dist
    plane shiftUp(double dist) { return {n, d + dist * abs(n)}; }
    // orthogonal projection of point p onto plane
    p3 proj(p3 p) { return p - n * side(p) / sq(n); }
    // orthogonal reflection of point p onto plane
    p3 refl(p3 p) { return p - n * 2 * side(p) / sq(n); }
    pair<p3, p3> get_two_points_on_plane() {
        assert(sign(n.x) != 0 || sign(n.y) != 0 || sign(n.z) != 0);
        if (sign(n.x) == 0 && sign(n.y) == 0) return {p3(1, 0, d/n.z),  p3(0, 1, d/n.z)};
        if (sign(n.y) == 0 && sign(n.z) == 0) return {p3(d/n.x, 1, 0),  p3(d/n.x, 0, 1)};
        if (sign(n.z) == 0 && sign(n.x) == 0) return {p3(1, d/n.y, 0),  p3(0, d/n.y, 1)};
        if (sign(n.x) == 0) return {p3(1, d/n.y, 0),  p3(0, 0, d/n.z)};
        if (sign(n.y) == 0) return {p3(0, 1, d/n.z),  p3(d/n.x, 0, 0)};
        if (sign(n.z) == 0) return {p3(d/n.x, 0, 1),  p3(0, d/n.y, 0)};
        if (sign(d)!=0) return {p3(d/n.x, 0, 0),  p3(0, d/n.y, 0)};
        return {p3(n.y, -n.x, 0),  p3(-n.y, n.x, 0)};
    }
};

struct coords {
    // coordinate system for coplanar points
    // o is the origin, dx, dy, dz are unit vectors similar to normal 3D system
    // but dx and dy are on the plane
    p3 o, dx, dy, dz;
    // From three points P, Q, R on the plane
    coords(p3 p, p3 q, p3 r) : o(p) {
        dx = unit(q - p);
        dz = unit(dx * (r - p));
        dy = dz * dx;
    }
    // From four points P,Q,R,S: take directions PQ, PR, PS as is
    // it allows us to keep using integer coordinates but has some pitfalls
    // e.g. distances and angles are not preserved but relative positions are (convex hull works)
    coords(p3 p, p3 q, p3 r, p3 s) :
                o(p), dx(q - p), dy(r - p), dz(s - p) {}
    // 2D position vector of point p in this coordinate system centered at o
    // p must be on the plane
    PT pos2d(p3 p) {
        return {(p - o) | dx, (p - o) | dy};
    }
    // returns the 3D position vector of point p in this new coordinate system
    // p can be outside the plane
    p3 pos3d(p3 p) {
        return {(p - o) | dx, (p - o) | dy, (p - o) | dz};
    }
    // given 2D position vector p centered at o, return the original 3D position vector
    p3 pos3d(PT p){
        return o + dx * p.x + dy * p.y;
    }
};

struct line3d {
    // d is the direction vector of the line
    p3 d, o; // p = o + k * d (k is a real parameter)
    line3d() {}
    // From two points P, Q
    line3d(p3 p, p3 q) : d(q - p), o(p) {}
    // From two planes p1, p2
    // assuming they are not parallel
    line3d(plane p1, plane p2) {
        d = p1.n * p2.n;
        o = (p2.n * p1.d - p1.n * p2.d) * d / sq(d);
        // o is actually the closest point on the line to the origin
    }
    double dist2(p3 p) { return sq(d * (p - o)) / sq(d); }
    double dist(p3 p) { return sqrt(dist2(p)); }
    // compare points by their projection on the line
    // so you can sort points on the line using this
    bool cmp_proj(p3 p, p3 q) { return (d | p) < (d | q); }
    // orthogonal projection of point p onto line
    p3 proj(p3 p) { return o + d * (d|(p - o)) / sq(d); }
    // orthogonal reflection of point p onto line
    p3 refl(p3 p) { return proj(p) * 2 - p; }
    // returns the intersection point of the line with plane p
    // assuming plane and line are not parallel
    p3 inter(plane p) {
        // assert((d | p.n) != 0); // no intersection if parallel
        return o - d * p.side(o) / (d | p.n);
    }
};

// smallest distance between two lines
double dist(line3d l1, line3d l2) {
    p3 n = l1.d * l2.d;
    if (n == zero) return l1.dist(l2.o); // parallel
    return fabs((l2.o - l1.o) | n) / abs(n);
}
// closest point from line l2 to line l1
p3 closest_on_l1(line3d l1, line3d l2) {
    p3 n2 = l2.d * (l1.d * l2.d);
    return l1.o + l1.d * ((l2.o - l1.o) | n2) / (l1.d | n2);
}
// small angle between direction vectors of two lines
double get_angle(line3d l1, line3d l2) {
    return small_angle(l1.d, l2.d);
}
bool is_parallel(line3d l1, line3d l2) {
    return l1.d * l2.d == zero;
}
bool is_perpendicular(line3d l1, line3d l2) {
    return sign((l1.d | l2.d)) == 0;
}
// small angle between normal vectors of two planes
double get_angle(plane p1, plane p2) {
    return small_angle(p1.n, p2.n);
}
bool is_parallel(plane p1, plane p2) {
    return p1.n * p2.n == zero;
}
bool is_perpendicular(plane p1, plane p2) {
    return sign((p1.n | p2.n)) == 0;
}
double get_angle(plane p, line3d l) {
    return PI / 2 - small_angle(p.n, l.d);
}
bool is_parallel(plane p, line3d l) {
    return sign((p.n | l.d)) == 0;
}
bool is_perpendicular(plane p, line3d l) {
    return p.n * l.d == zero;
}
// returns the line perpendicular to plane p and passing through point o
line3d perp_through(plane p, p3 o) {return line3d(o, o + p.n);}
// returns the plane perpendicular to line l and passing through point o
plane perp_through(line3d l, p3 o) {return plane(l.d, o);}

// returns two points on intesection line of two planes formed by points
// a1, b1, c1 and a2, b2, c2 respectively
pair<p3, p3> plane_plane_intersection(p3 a1, p3 b1, p3 c1, p3 a2, p3 b2, p3 c2) {
    p3 n1 = (b1 - a1) * (c1 - a1);
    p3 n2 = (b2 - a2) * (c2 - a2);
    double d1 = n1 | a1, d2 = n2 | a2;
    p3 d = n1 * n2;
    if (d == zero) return make_pair(zero, zero);
    p3 o = (n2 * d1 - n1 * d2) * d / (d | d);
    return make_pair(o, o + d);
}
// returns center of circle passing through three
// non-colinear and co-planer points a, b and c
p3 circle_center(p3 a, p3 b, p3 c) {
    p3 v1 = b - a, v2 = c - a;
    double v1v1 = v1 | v1, v2v2 = v2 | v2, v1v2 = v1 | v2;
    double base = 0.5 / (v1v1 * v2v2 - v1v2 * v1v2);
    double k1 = base * v2v2 * (v1v1 - v1v2);
    double k2 = base * v1v1 * (v2v2 - v1v2);
    return a + v1 * k1 + v2 * k2;
}
// segment ab to point c
double distance_from_segment_to_point(p3 a, p3 b, p3 c) {
    if (sign(dot(b - a, c - a)) < 0) return dist(a, c);
    if (sign(dot(a - b, c - b)) < 0) return dist(b, c);
    return fabs(cross((b - a).unit(), c - a).abs());
}
double distance_from_triangle_to_point(p3 a, p3 b, p3 c, p3 d) {
        plane P(a, b, c);
        p3 proj = P.proj(d);
    double dis = min(distance_from_segment_to_point(a, b, d), min(distance_from_segment_to_point(b, c, d), distance_from_segment_to_point(c, a, d)));
    int o = sign(orient_by_normal(a, b, proj, P.n));
    int inside = o == sign(orient_by_normal(b, c, proj, P.n));
    inside &= o == sign(orient_by_normal(c, a, proj, P.n));
    if (inside) return (d - proj).abs();
    return dis;
}
double distance_from_triangle_to_segment(p3 a, p3 b, p3 c, p3 d, p3 e) {
    double l = 0.0, r = 1.0;
    int cnt = 100;
    double ret = inf;
    while (cnt--) {
        double mid1 = l + (r - l) / 3.0, mid2 = r - (r - l) / 3.0;
        double x = distance_from_triangle_to_point(a, b, c, d + (e - d) * mid1);
        double y = distance_from_triangle_to_point(a, b, c, d + (e - d) * mid2);
        if (x < y) {
            r = mid2;
            ret = x;
        }
        else {
            ret = y;
            l = mid1;
        }
    }
    return ret;
}
// triangles are solid
double distance_from_triangle_to_triangle(p3 a, p3 b, p3 c, p3 d, p3 e, p3 f) {
    double ret = inf;
    ret = min(ret, distance_from_triangle_to_segment(a, b, c, d, e));
    ret = min(ret, distance_from_triangle_to_segment(a, b, c, e, f));
    ret = min(ret, distance_from_triangle_to_segment(a, b, c, f, d));
    ret = min(ret, distance_from_triangle_to_segment(d, e, f, a, b));
    ret = min(ret, distance_from_triangle_to_segment(d, e, f, b, c));
    ret = min(ret, distance_from_triangle_to_segment(d, e, f, c, a));
    return ret;
}


bool operator < (p3 p, p3 q) {
    return tie(p.x, p.y, p.z) < tie(q.x, q.y, q.z);
}
struct edge {
    int v;
    bool same; // is the common edge between two faces in the same order?
};
// Given a series of faces (lists of points) of a polyhedron, reverse some of them
// so that their orientations are consistent (all area vectors of the faces either pointing outwards or inwards)
// just compute the area vector of one face to see if it’s pointing outwards or inwards
vector<vector<p3>> reorient(vector<vector<p3>> fs) {
    int n = fs.size();
        // Find the common edges and create the resulting graph
    vector<vector<edge>> g(n);
    map<pair<p3,p3>, int> es;
    for (int u = 0; u < n; u++) {
        for (int i = 0, m = fs[u].size(); i < m; i++) {
            p3 a = fs[u][i], b = fs[u][(i + 1) % m];
                        // Let’s look at edge a-b
            if (es.count({a, b})) { // seen in same order
                int v = es[{a, b}];
                g[u].push_back({v, true});
                g[v].push_back({u, true});
            }
            else if (es.count({b, a})) { // seen in different order
                int v = es[ {b, a}];
                g[u].push_back({v,false});
                g[v].push_back({u,false});
            }
            else { // not seen yet
                es[{a,b}] = u;
            }
        }
    }
        // Perform BFS to find which faces should be flipped
    vector<bool> vis(n,false), flip(n);
    flip[0] = false;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (edge e : g[u]) {
            if (!vis[e.v]) {
                vis[e.v] = true;
                                // If the edge was in the same order,
                                // exactly one of the two should be flipped
                flip[e.v] = (flip[u] ^ e.same);
                q.push(e.v);
            }
        }
    }
        // Actually perform the flips
    for (int u = 0; u < n; u++)
        if (flip[u]) {
            reverse(fs[u].begin(), fs[u].end());
        }
    return fs;
}

// O(n^2), O(n) faces in the hull
struct CH3D {
    struct face {
        int a, b, c; // the number of three points on one face of the convex hull
        bool ok;  // whether the face belongs to the face on the final convex hull
    };
    int n; // initial vertex number
    vector<p3> P;
    int num; // convex hull surface triangle number
    vector<face> F; // convex surface triangles
    vector<vector<int>> g;

    void init(vector<p3> p) {
        P = p;
        n = p.size();
        F.resize(8 * n + 1);
        g.resize(n + 1, vector<int> (n + 1));
    }

    double len(p3 a) {
        return sqrt(a | a);
    }
    p3 cross(const p3 &a, const p3 &b, const p3 &c) {
        return (b - a) * (c - a);
    }
    double area(p3 a, p3 b, p3 c) {
        return len((b - a) * (c - a));
    }
    double volume(p3 a, p3 b, p3 c, p3 d) {
        return (b - a) * (c - a) | (d - a);
    }
    // positive: p3 in the same direction
    double dblcmp(p3 &p, face &f) {
        p3 m = P[f.b] - P[f.a];
        p3 n = P[f.c] - P[f.a];
        p3 t = p - P[f.a];
        return (m * n) | t;
    }
    void deal(int p, int a, int b) {
        int f = g[a][b]; // search for another plane adjacent to the edge
        face add;
        if (F[f].ok) {
            if (dblcmp(P[p], F[f]) > eps) dfs(p, f);
            else {
                add.a = b;
                add.b = a;
                add.c = p; // pay attention to the order here, to be right-handed
                add.ok = true;
                g[p][b] = g[a][p] = g[b][a] = num;
                F[num++] = add;
            }
        }
    }
    // recursively search all faces that should be removed from the convex hull
    void dfs(int p, int now) {
        F[now].ok = 0;
        deal(p, F[now].b, F[now].a);
        deal(p, F[now].c, F[now].b);
        deal(p, F[now].a, F[now].c);
    }
    bool same(int s, int t) {
        p3 &a = P[F[s].a];
        p3 &b = P[F[s].b];
        p3 &c = P[F[s].c];
        return fabs(volume(a, b, c, P[F[t].a])) < eps &&
               fabs(volume(a, b, c, P[F[t].b])) < eps &&
               fabs(volume(a, b, c, P[F[t].c])) < eps;
    }
    // building a 3D convex hull
    void create_hull() {
        int i, j, tmp;
        face add;
        num = 0;
        if (n < 4)return;

        // ensure that the first four points are not coplanar
        bool flag = true;
        for (i = 1; i < n; i++) {
            if (len(P[0] - P[i]) > eps) {
                swap(P[1], P[i]);
                flag = false;
                break;
            }
        }
        if (flag) return;
        flag = true;
        // make the first three points not collinear
        for (i = 2; i < n; i++) {
            if (len((P[0] - P[1]) * (P[1] - P[i])) > eps) {
                swap(P[2], P[i]);
                flag = false;
                break;
            }
        }
        if (flag) return;
        flag = true;
        // make the first four points not coplanar
        for (int i = 3; i < n; i++) {
            if (fabs((P[0] - P[1]) * (P[1] - P[2]) | (P[0] - P[i])) > eps) {
                swap(P[3], P[i]);
                flag = false;
                break;
            }
        }
        if (flag) return;

        for (i = 0; i < 4; i++) {
            add.a = (i + 1) % 4;
            add.b = (i + 2) % 4;
            add.c = (i + 3) % 4;
            add.ok = true;
            if (dblcmp(P[i], add) > 0)swap(add.b, add.c);
            g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
            F[num++] = add;
        }
        for (i = 4; i < n; i++) {
            for (j = 0; j < num; j++) {
                if (F[j].ok && dblcmp(P[i], F[j]) > eps) {
                    dfs(i, j);
                    break;
                }
            }
        }
        tmp = num;
        for (i = num = 0; i < tmp; i++)
            if (F[i].ok) F[num++] = F[i];

    }
    double surface_area() {
        double res = 0;
        if (n == 3) {
            p3 p = cross(P[0], P[1], P[2]);
            res = len(p) / 2.0;
            return res;
        }
        for(int i = 0; i < num; i++) {
            res += area(P[F[i].a], P[F[i].b], P[F[i].c]);
        }
        return res / 2.0;
    }
    double volume() {
        double res = 0;
        p3 tmp(0, 0, 0);
        for(int i = 0; i < num; i++) {
            res += volume(tmp, P[F[i].a], P[F[i].b], P[F[i].c]);
        }
        return fabs(res / 6.0);
    }
    int number_of_triangles() { // number of surface triangles
        return num;
    }
    int number_of_polygons() {  // number of surface polygons
        int i, j, res, flag;
        for (i = res = 0; i < num; i++) {
            flag = 1;
            for (j = 0; j < i; j++) {
                if (same(i, j)) {
                    flag = 0;
                    break;
                }
            }
            res += flag;
        }
        return res;
    }
    p3 centroid() { // center of gravity
        p3 ans(0, 0, 0), o(0, 0, 0);
        double all = 0;
        for (int i = 0; i < num; i++) {
            double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
            ans = ans + (o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0 * vol;
            all += vol;
        }
        ans = ans / all;
        return ans;
    }
    double point_to_face_distance(p3 p, int i) {
        return fabs(volume(P[F[i].a], P[F[i].b], P[F[i].c], p) / len((P[F[i].b] - P[F[i].a]) * (P[F[i].c] - P[F[i].a])));
    }
};

// https://desktop.arcgis.com/en/arcmap/10.7/map/projections/geographic-coordinate-system.htm
// given the radius of the sphere, latitude and longitude of a point in degrees
// return the 3D coordinates of the point on the sphere assuming the sphere is centered at the origin
p3 get_sphere(double r, double lat, double lon) {
    lat *= PI / 180, lon *= PI / 180;
    return {r * cos(lat) * cos(lon), r * cos(lat) * sin(lon), r * sin(lat)};
}
int sphere_line_intersection(p3 o, double r, line3d l, pair<p3,p3> &out) {
    double h2 = r * r - l.dist2(o);
    if (h2 < 0) return 0; // the line doesn’t touch the sphere
    p3 p = l.proj(o);
    p3 h = l.d * sqrt(h2)/abs(l.d); // vector parallel to l, of length h
    out = {p - h, p + h};
    return 1 + (h2 > 0);
}
// The shortest distance between two points A and B on a sphere (O, r) is
// given by travelling along plane OAB and on the surface of the sphere. It is called the great-circle distance
// if a and b are outside the sphere, then it will give the distance between their projections on the sphere
double great_circle_dist(p3 o, double r, p3 a, p3 b) {
    // s = r * theta
    return r * get_angle(a - o, b - o);
}

// Assume that the sphere is centered at the origin
// We will call a segment [AB] valid if A and B are not
// opposite each other on the sphere
bool validSegment(p3 a, p3 b) {
    return a * b != zero || (a | b) > 0;
}

bool proper_intersection(p3 a, p3 b, p3 c, p3 d, p3 &out) {
    p3 ab = a * b, cd = c * d; // normals of planes OAB and OCD
    int oa = sign(cd | a),
        ob = sign(cd | b),
        oc = sign(ab | c),
        od = sign(ab | d);
    out = ab * cd * od; // four multiplications => careful with overflow!
    return (oa != ob && oc != od && oa != oc);
}

// Assume that the sphere is centered at the origin
bool point_on_sphere_segment(p3 a, p3 b, p3 p) {
    p3 n = a*b;
    if (n == zero)
        return a * p == zero && (a | p) > 0;
    return (n | p) == 0 && (n | a * p) >= 0 && (n | b * p) <= 0;
}

struct DirectionSet : vector<p3> {
    using vector::vector; // import constructors
    void insert(p3 p) {
        for (p3 q : *this) if (p*q == zero) return;
        push_back(p);
    }
};
// Assume that the sphere is centered at the origin
// it returns the direction vectors of the intersection points
// to get the actual points, scale the direction vectors to the radius of the sphere
DirectionSet segment_segment_intersection_on_sphere(p3 a, p3 b, p3 c, p3 d) {
    assert(validSegment(a, b) && validSegment(c, d));
    p3 out;
    if (proper_intersection(a, b, c, d, out)) return {out};
    DirectionSet s;
    if (point_on_sphere_segment(c, d, a)) s.insert(a);
    if (point_on_sphere_segment(c, d, b)) s.insert(b);
    if (point_on_sphere_segment(a, b, c)) s.insert(c);
    if (point_on_sphere_segment(a, b, d)) s.insert(d);
    return s;
}

// small angle between spherical segments ab and ac
// assume that the sphere is centered at the origin
// all points a, b, c are on the sphere
double angle_on_sphere(p3 a, p3 b, p3 c) {
    return get_angle(a * b, a * c);
}

// oriented angle between spherical segments ab and ac
// that is how much we rotate counterclockwise to get from ab to ac
// assume that the sphere is centered at the origin
// all points a, b, c are on the sphere
double oriented_angle_on_sphere(p3 a, p3 b, p3 c) {
    if ((a * b | c) >= 0) return angle_on_sphere(a, b, c);
    else return 2 * PI - angle_on_sphere(a, b, c);
}

// Assume that the sphere is centered at the origin
// the polygon is simple and given in counterclockwise order
// for each consecutive pair of points, the counterclockwise left
// part of the segment is considered to be inside the surface area that the polygon encloses
// if the polygon is outside the sphere, the projection of the polygon on the sphere will be considered
double area_on_the_surface_of_the_sphere(double r, vector<p3> p) {
    int n = p.size();
    double sum = -(n - 2) * PI;
    for (int i = 0; i < n; i++) {
        sum += oriented_angle_on_sphere(p[(i + 1) % n], p[(i + 2) % n], p[i]);
    }
    return r * r * sum;
}

// Assume that O is the origin
// it returns 0 if O is outside the polyhedron
// 1 if O is inside the polyhedron, and the vector areas of the faces are oriented towards the outside;
// −1 if O is inside the polyhedron, and the vector areas of the faces are oriented towards the inside.
int winding_number_3D(vector<vector<p3>> fs) {
    double sum = 0;
    for (vector<p3> f : fs) {
        sum += remainder(area_on_the_surface_of_the_sphere(1, f), 4 * PI);
    }
    return round(sum / (4 * PI));
}

struct sphere {
    p3 c;
    double r;
    sphere() {}
    sphere(p3 c, double r) : c(c), r(r) {}
};

// spherical cap is a portion of a sphere cut off by a plane
// https://en.wikipedia.org/wiki/Spherical_cap
struct spherical_cap {
    p3 c;
    double r;
    spherical_cap() {}
    spherical_cap(p3 c, double r) : c(c), r(r) {}

    // angle th is the polar angle between the rays from the center of the sphere to one edge of the cap
    // and orthogonal line from the center of the sphere to the plane of the cap

    // height of the cap (just like real world cap)
    double height(double th)      {
        return r * (1 - cos(th));
    }
    // radius of the base of the cap
    double base_radius(double th)  {
        return r * sin(th);
    }
    // volume of the cap
    double volume(double th)      {
        double h = height(th);
        return PI * h * h * (3 * r - h) / 3.0;
    }
    // surface area of the cap
    double surface_area(double th) {
        double h = height(th);
        return 2 * PI * r * h;
    }
};

// returns the sphere passing through four points
sphere circumscribed_sphere(p3 a, p3 b, p3 c, p3 d) {
    assert( sign(plane(a, b, c).side(d)) != 0);

    plane u = plane(a - b, (a + b) / 2);
    plane v = plane(b - c, (b + c) / 2);
    plane w = plane(c - d, (c + d) / 2);

    assert(!is_parallel(u, v));
    assert(!is_parallel(v, w));
    line3d l1(u, v), l2(v, w);
    assert( sign(dist(l1, l2)) == 0);

    p3 C = closest_on_l1(l1, l2);
    return sphere(C, abs(C - a));
}

// https://mathworld.wolfram.com/Sphere-SphereIntersection.html
// it won't work if one sphere is totally inside the other sphere
// handle that case separately
// returns the surface area and volume of the intersection
pair<double, double> sphere_sphere_intersection(sphere s1, sphere s2) {
    double d = abs(s1.c - s2.c);
    if(sign(d - s1.r - s2.r) >= 0) return {0, 0}; // not intersecting
    // only the distance matters, so we will now consider the centers
    // of the big sphere to be (0, 0, 0) and (d, 0, 0) for the small sphere
    // we can transform the results back to w.r.t the real centers if we want

    double R = max(s1.r, s2.r);
    double r = min(s1.r, s2.r);
    double y = R + r - d;
    double x = (R * R - r * r + d * d) / (2 * d);
    // the intersecting plane is parallel to the yz plane
    // with the above x value as its x coordinate
    double w = d * d - r * r  + R * R;
    double a = sqrt(4 * d * d * R * R - w * w) / (2.0 * d);
    // a is the radius of the intersecting circle on the intersecting plane
    // with center (x, 0)
    double h1 = R - x;
    double h2 = y - h1;
    // h1 is the height of the intersecting spherical cap of the big sphere
    // h2 is for the small sphere

    // total volume of the whole intersection = sum of the volumes of the spherical caps
    double volume      = PI * h1 * h1 * (3 * R - h1) / 3.0 + PI * h2 * h2 * (3 * r - h2) / 3.0;
    // total surface area of the intersecting spherical caps
    double surface_area = 2 * PI * R * h1 + 2 * PI * r * h2;
    return make_pair(surface_area, volume);
}

sphere smallest_enclosing_sphere(vector<p3> p) {
    int n = p.size();
    p3 c(0, 0, 0);
    for(int i = 0; i < n; i++) c = c + p[i];
    c = c / n;

    double ratio = 0.1;
    int pos = 0;
    int it = 100000;
    while (it--) {
        pos = 0;
        for (int i = 1; i < n; i++) {
            if(sq(c - p[i]) > sq(c - p[pos])) pos = i;
        }
        c = c + (p[pos] - c) * ratio;
        ratio *= 0.998;
    }
    return sphere(c, abs(c - p[pos]));
}

// it returns the angle of the spherical cap that is formed by the intersection of all tangents
double tangent_from_point_to_sphere(p3 p, sphere s) {
    double d = abs(p - s.c);
    if (sign(d - s.r) < 0) return -1; // inside the sphere, so no tangent
    if (sign(d - s.r) == 0) return -2; // on the sphere, handle separately
    double tangent_length = sqrt(d * d - s.r * s.r);
    double th = acos(s.r / d);
    return th;
}


struct pyramid {
        int n;     // number of sides of the pyramid
        double l;  // length of each side
        double ang;
        pyramid(int _n, double _l) {
            n = _n;
            l = _l;
            ang = PI / n;
        }
        double base_area() {
            return l * l * n / (4 * tan(ang));
        }
        double height() {
            return l * sqrt(1 - 1 / (4 * sin(ang) * sin(ang)) );
        }
        double volume() {
            return base_area() * height() / 3;
        }
};

struct cylinder {
    double r, h; // radius and height
    cylinder(double _r, double _h) {
        r = _r;
        h = _h;
    }
    double volume() {
        return PI * r * r * h;
    }
    double surface_area() {
        return 2 * PI * r * h + 2 * PI * r * r;
    }
};

struct cone {
    double r, h; // radius and height
    cone(double _r, double _h) {
        r = _r;
        h = _h;
    }
    double volume() {
        return PI * r * r * h / 3.0;
    }
    double surface_area() {
        return PI * r * (r + sqrt(h * h + r * r));
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}