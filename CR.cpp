const int B = 2500;
struct query {
    ll l, r, t, id;
    bool operator < (const query &x) const {
        if (l / B == x.l / B) {
            if (r / B == x.r / B) return t < x.t;
            return r / B < x.r / B;
        }
        return l / B < x.l / B;
    }
