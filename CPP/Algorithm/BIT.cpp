// Note: Binary Indexed Tree (BIT) is also known as Fenwick Tree and it is based on prefix sum concept. (0-based indexing)
https://cses.fi/problemset/task/1651

struct bit {
    int n; vector<int64_t> tre;
    bit(int _n) : n(_n + 5), tre(n) {}
    void add(int in, int64_t val) {
        for (++in; in <= n; in += in & -in) tre[in] += val;
    }
    void add(int l, int r, int64_t val) { add(l, val); add(++r, -val); }
    int64_t get(int in) {
        int64_t tot = 0;
        for (++in; in > 0; in -= in & -in) tot += tre[in];
        return tot;
    }
    int64_t get(int l, int r) { return get(r) - get(--l); }
};

// OR, Range Update & Range Query:

struct bit {
    int n; vector<int64_t> pro, sum;
    bit(int _n) : n(_n + 5), pro(n), sum(n) {}
    void up(int i, int64_t mul, int64_t add) {
        while (i < n) {
            pro[i] += mul; sum[i] += add; i |= (i + 1);
        }
    }
    void add(int l, int r, int64_t val) {
        up(l, val, -val * (l - 1)); up(r, -val, val * r);
    }
    int64_t get(int i) {
        int64_t mul = 0, add = 0, st = i;
        while (i >= 0) {
            mul += pro[i]; add += sum[i]; i = (i & (i + 1)) - 1;
        }
        return (mul * st + add);
    }
    int64_t get(int l, int r) { return get(r) - get(--l); }
};

// lower_bound of Prefix Sum:
https://codeforces.com/contest/1354/problem/D

int64_t bit[N];
int lb(int64_t val) {
    int pos = 0;
	for (int i = log2(N); i >= 0; --i) {
        int ex = 1 << i;
        if (pos + ex < N && bit[pos + ex] < val) {
			val -= bit[pos + ex]; pos += ex;
		}
	}
	return pos + 1;
}

// 2-D BIT: (1-based indexing)

struct bit {
    int n; vector<vector<int64_t>> tre;
    bit(int _n) : n(_n + 5), tre(n, vector<int64_t>(n)) {}
    void add(int x, int y, int64_t val) {
        for (; x < n; x += -x & x) {
            for (int j = y; j < n; j += -j & j) tre[x][j] += val;
        }
    }
    int64_t get(int x, int y) {
        int64_t ans = 0;
        for (; x; x -= x & -x) {
            for (int j = y; j; j -= j & -j) ans += tre[x][j];
        }
        return ans;
    }
    int64_t get(int x1, int y1, int x2, int y2) {
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};

// 2-D BIT with Range Update & Range Query:

struct bit {
    int n; vector<vector<vector<int64_t>>> pro, sum;
    bit(int _n) : n(_n + 5), pro(n, vector<vector<int64_t>>(n, vector<int64_t>(2))), sum(n, vector<vector<int64_t>>(n, vector<int64_t>(2))) {}
    void up2(auto &t, int x, int y, int64_t mul, int64_t add) {
        for (int i = x; i < n; i += i & -i) {
            for (int j = y; j < n; j += j & -j) {
                t[i][j][0] += mul; t[i][j][1] += add;
            }
        }
    }
    void up1(int x, int y1, int y2, int64_t mul, int64_t add) {
        up2(pro, x, y1, mul, -mul * (y1 - 1)); up2(pro, x, y2, -mul, mul * y2);
        up2(sum, x, y1, add, -add * (y1 - 1)); up2(sum, x, y2, -add, add * y2);
    }
    void add(int x1, int y1, int x2, int y2, int64_t val) {
        up1(x1, y1, y2, val, -val * (x1 - 1)); up1(x2, y1, y2, -val, val * x2);
    }
    int64_t get2(auto &t, int x, int y) {
        int64_t mul = 0, add = 0;
        for (int i = y; i > 0; i -= i & -i) { mul += t[x][i][0]; add += t[x][i][1]; }
        return (mul * y + add);
    }
    int64_t get1(int x, int y) {
        int64_t mul = 0, add = 0;
        for (int i = x; i > 0; i -= i & -i) { mul += get2(pro, i, y); add += get2(sum, i, y); }
        return (mul * x + add);
    }
    int64_t get(int x1, int y1, int x2, int y2) {
        return get1(x2, y2) - get1(x1 - 1, y2) - get1(x2, y1 - 1) + get1(x1 - 1, y1 - 1);
    }
};

// Operation:
    int n, m; cin >> n >> m; bit t(n);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            int64_t v; cin >> v; t.add(i, j, i, j, v);
        }
    }
    int q; cin >> q;
    while (q--) {
        int ty, x1, y1, x2, y2; cin >> ty;
        if(ty == 2) {
            int64_t val; cin >> x1 >> y1 >> x2 >> y2 >> val;
            t.add(x1, y1, x2, y2, val);
        }
        else {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << t.get(x1, y1, x2, y2) << '\n';
        }
    }

// OR, Only to make the position(x, y) on or off and get the summation:

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct bit {
    int n; vector<oset<pair<int, int>>> tre;
    bit(int _n) : n(_n + 5), tre(n) {}
    void on(int x, int y) {
        for (int i = x; i < n; i += i & -i) tre[i].insert({y, x});
    }
    void off(int x, int y) {
        for (int i = x; i < n; i += i & -i) tre[i].erase({y, x});
    }
    int get(int x, int y) {
        int ans = 0; ++y;
        for (int i = x; i > 0; i -= i & -i) ans += tre[i].order_of_key({y, 0});
        return ans;
    }
    int64_t get(int x1, int y1, int x2, int y2) {
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};

// Dynamic BIT:
https://cses.fi/problemset/task/1144

struct bit {
    int n; vector<int64_t> tre, sal;
    bit(int _n, auto &_sal) : n(_n + 5), tre(n << 1), sal(_sal) {}
    void add(int in, int64_t val) {
        int i = upper_bound(sal.begin(), sal.end(), in) - sal.begin();
        for (; i < (n << 1); i += i & (-i)) tre[i] += val;
    }
    int64_t get(int in) {
        int64_t res = 0, i = upper_bound(sal.begin(), sal.end(), in) - sal.begin();
        for (; i; i -= i & (-i)) res += tre[i]; return res;
    }
    int64_t get(int l, int r) { return get(r) - get(--l); }
};

// Operation:
	int64_t n, q; cin >> n >> q;
    vector<int64_t> ar(n), sal;
    for (i = 0; i < n; ++i) {
        cin >> ar[i]; sal.push_back(ar[i]);
    }
    vector<array<int64_t, 3>> query;
    while (q--) {
		char ch; int64_t a, b; cin >> ch >> a >> b;
		query.push_back({ch == '!', a, b});
		if (ch == '!') sal.push_back(b);
	}
	sort(sal.begin(), sal.end());
	sal.erase(unique(sal.begin(), sal.end()), sal.end());
    bit t(n, sal); for (auto e : ar) t.add(e, 1);
	for (auto [f, l, r] : query) {
		if (f) {
			t.add(ar[--l], -1); ar[l] = r; t.add(ar[l], 1);
		}
        else cout << t.get(l, r) << '\n';
	}
