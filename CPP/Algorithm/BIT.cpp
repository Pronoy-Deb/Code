// Complexity: O()
// Note: Binary Indexed Tree (BIT) is also known as Fenwick Tree. (1-based indexing)

long long bit[N], n;
void up(int in, long long val) {
    for (in++; in < n; in += in & -in) bit[in] += val;
}
long long get(int in) {
    long long tot = 0;
    for (in++; in > 0; in -= in & -in) tot += bit[in];
    return tot;
}
long long get(int l, int r) { return get(r) - get(l - 1); }

// OR,

template <class T>
struct BIT { // 1-indexed
int n; vector<T> t;
BIT() {}
BIT(int _n) {
    n = _n; t.assign(n + 1, 0);
}
T get(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
}
void up(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
}
void up(int l, int r, T val) {
    up(l, val); up(r + 1, -val);
}
T get(int l, int r) { return get(r) - get(l - 1); }
};

// OR,

// struct BIT {
long long M[N], A[N];
// BIT() {
//     memset(M, 0, sizeof M); memset(A, 0, sizeof A);
// }
void upd(int i, long long mul, long long add) {
    while (i < N) {
        M[i] += mul; A[i] += add; i |= (i + 1);
    }
}
void up(int l, int r, long long val) {
    upd(l, val, -val * (l - 1)); upd(r, -val, val * r);
}
long long get(int i) {
    long long mul = 0, add = 0, st = i;
    while (i >= 0) {
        mul += M[i]; add += A[i]; i = (i & (i + 1)) - 1;
    }
    return (mul * st + add);
}
long long get(int l, int r) { return get(r) - get(l - 1); }
// } t;

// 2-D BIT:

long long bit[N][N];
void add(int x, int y, long long val) {
    for (; x < N; x += -x & x) {
        for (int j = y; j < N; j += -j & j) bit[x][j] += val;
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

// OR,

struct BIT2D {
long long M[N][N][2], A[N][N][2];
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
void up(int x1, int y1, int x2, int y2, long long val) {
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
            cin >> k; t.up(i, j, i, j, k);
        }
    }
    cin >> q;
    while(q--) {
        int ty, x1, y1, x2, y2; cin >> ty;
        if(ty == 1) {
            long long val; cin >> x1 >> y1 >> x2 >> y2 >> val;
            t.up(x1, y1, x2, y2, val); // add val from top-left(x1, y1) to bottom-right (x2, y2);
        }
        else {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << t.get(x1, y1, x2, y2) << '\n'; // output sum from top-left(x1, y1) to bottom-right (x2, y2);
        }
    }

// Dynamic BIT:
// Problem: https://cses.fi/problemset/task/1144

long long bit[N << 1]; vector<long long> sal;
void up(int in, long long val) {
    int i = upper_bound(sal.begin(), sal.end(), in) - sal.begin();
	for (; i < (N << 1); i += i & (-i)) bit[i] += val;
}
long long get(int in) {
	long long res = 0, i = upper_bound(sal.begin(), sal.end(), in) - sal.begin();
	for (; i; i -= i & (-i)) res += bit[i]; return res;
}
long long get(int l, int r) { return get(r) - get(l - 1); }

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
	for (auto &e : ar) up(e, 1);
	for (auto &[f, s, t] : query) {
		if (f) {
			up(ar[--s], -1); ar[s] = t; up(ar[s], 1);
		}
        else cout << get(s, t) << '\n';
	}
