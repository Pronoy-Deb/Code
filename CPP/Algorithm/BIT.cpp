// Note: Binary Indexed Tree (BIT) is also known as Fenwick Tree and it is based on prefix sum concept. (0-based indexing)
https://cses.fi/problemset/task/1651

long long bit[N], n;
void add(int in, long long val) {
    for (++in; in <= n; in += in & -in) bit[in] += val;
}
void add(int l, int r, long long val) { add(l, val); add(++r, -val); }
long long get(int in) {
    long long tot = 0;
    for (++in; in > 0; in -= in & -in) tot += bit[in];
    return tot;
}
long long get(int l, int r) { return get(r) - get(--l); }
void reset() { for (int i = 0; i <= n; ++i) bit[i] = 0; }

// OR, Range Update & Range Query:

long long pro[N], bit[N]; set<int> ind;
void up(int i, long long mul, long long add) {
    while (i < N) {
        // ind.insert(i);
        pro[i] += mul; bit[i] += add; i |= (i + 1);
    }
}
void add(int l, int r, long long val) {
    up(l, val, -val * (l - 1)); up(r, -val, val * r);
}
long long get(int i) {
    long long mul = 0, add = 0, st = i;
    while (i >= 0) {
        mul += pro[i]; add += bit[i]; i = (i & (i + 1)) - 1;
    }
    return (mul * st + add);
}
long long get(int l, int r) { return get(r) - get(--l); }
void reset() { for (auto &i : ind) pro[i] = bit[i] = 0; ind.clear(); }

// lower_bound of Prefix Sum:
https://codeforces.com/contest/1354/problem/D

long long bit[N];

int lb(long long val) {
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

long long bit[N][N]; set<pair<int, int>> ind;
void add(int x, int y, long long val) {
    for (; x < N; x += -x & x) {
        for (int j = y; j < N; j += -j & j) {
            // ind.insert({x, j});
            bit[x][j] += val;
        }
    }
}
long long get(int x, int y) {
    long long ans = 0;
    for (; x; x -= x & -x) {
        for (int j = y; j; j -= j & -j) ans += bit[x][j];
    }
    return ans;
}
long long get(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
}
void reset() { for (auto &[i, j] : ind) bit[i][j] = 0; ind.clear(); }

// OR,

struct BIT2D {
long long M[N][N][2], ar[N][N][2];
BIT2D() {
    memset(M, 0, sizeof M); memset(A, 0, sizeof A);
}
void up2(long long t[N][N][2], int x, int y, long long mul, long long add) {
    for(int i = x; i < N; i += i & -i) {
        for(int j = y; j < N; j += j & -j) {
            t[i][j][0] += mul; t[i][j][1] += add;
        }
    }
}
void up1(int x, int y1, int y2, long long mul, long long add) {
    up2(M, x, y1, mul, -mul * (y1 - 1));
    up2(M, x, y2, -mul, mul * y2);
    up2(A, x, y1, add, -add * (y1 - 1));
    up2(A, x, y2, -add, add * y2);
}
void add(int x1, int y1, int x2, int y2, long long val) {
    up1(x1, y1, y2, val, -val * (x1 - 1));
    up1(x2, y1, y2, -val, val * x2);
}
long long get2(long long t[N][N][2], int x, int y) {
    long long mul = 0, add = 0;
    for(int i = y; i > 0; i -= i & -i) {
        mul += t[x][i][0]; add += t[x][i][1];
    }
    return mul * y + add;
}
long long get1(int x, int y) {
    long long mul = 0, add = 0;
    for(int i = x; i > 0; i -= i & -i) {
        mul += get2(M, i, y); add += get2(A, i, y);
    }
    return mul * x + add;
}
long long get(int x1, int y1, int x2, int y2) {
    return get1(x2, y2) - get1(x1 - 1, y2) - get1(x2, y1 - 1) + get1(x1 - 1, y1 - 1);
}
} t;

// Operation:
    cin >> n >> m;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= m; j++) {
            cin >> k; t.add(i, j, i, j, k);
        }
    }
    cin >> q;
    while(q--) {
        int ty, x1, y1, x2, y2; cin >> ty;
        if(ty == 1) {
            long long val; cin >> x1 >> y1 >> x2 >> y2 >> val;
            t.add(x1, y1, x2, y2, val); // add val from top-left(x1, y1) to bottom-right (x2, y2);
        }
        else {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << t.get(x1, y1, x2, y2) << '\n'; // output sum from top-left(x1, y1) to bottom-right (x2, y2);
        }
    }

// Dynamic BIT:
// Problem: https://cses.fi/problemset/task/1144

long long bit[N << 1]; vector<long long> sal; set<int> ind;
void add(int in, long long val) {
    int i = upper_bound(sal.begin(), sal.end(), in) - sal.begin();
	for (; i < (N << 1); i += i & (-i)) {
        // ind.insert(i);
        bit[i] += val;
    }
}
long long get(int in) {
	long long res = 0, i = upper_bound(sal.begin(), sal.end(), in) - sal.begin();
	for (; i; i -= i & (-i)) res += bit[i]; return res;
}
long long get(int l, int r) { return get(r) - get(--l); }.
void reset() { for (auto &i : ind) bit[i] = 0; ind.clear(); sal.clear(); }

// Operation:
	cin >> n >> q;
    vector<long long> ar(n);
    for (i = 0; i < n; ++i) {
        cin >> ar[i]; sal.push_back(ar[i]);
    }
    vector<array<long long, 3>> query;
    while (q--) {
		char ch; long long a, b; cin >> ch >> a >> b;
		query.push_back({ch == '!', a, b});
		if (ch == '!') sal.push_back(b);
	}
	sort(sal.begin(), sal.end());
	sal.erase(unique(sal.begin(), sal.end()), sal.end());
	for (auto &e : ar) add(e, 1);
	for (auto &[f, s, t] : query) {
		if (f) {
			add(ar[--s], -1); ar[s] = t; add(ar[s], 1);
		}
        else cout << get(s, t) << '\n';
	}