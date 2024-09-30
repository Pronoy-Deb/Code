// Disjoint Sparse Table: O(nlogn) preprocessing, O(1) query
// https://www.codechef.com/problems/SEGPROD

int mod;
struct DST {
vector<vector<int>> left, right;
int k, n;
DST(vector<int> &ar) {
	n = ar.size(); k = log2(n) + 2;
	left.assign(k + 1, vector<int>(n));
	right.assign(k + 1, vector<int>(n));
	for (int j = 0; (1 << j) <= n; ++j) {
		long long mask = (1 << j) - 1, nw = 1; // neutral
		for (int i = 0; i < n; ++i) {
			nw = nw * ar[i] % mod; // prefix value
			left[j][i] = nw;
			if ((i & mask) == mask) nw = 1; // neutral
		}
		nw = 1; // neutral
		for (int i = n - 1; i >= 0; --i) {
			nw = nw * ar[i] % mod; // prefix value
			right[j][i] = nw;
			if ((i & mask) == 0) nw = 1; // neutral
		}
	}
}
long long get(int l, int r) {
	if (l == r) return left[0][l];
	long long i = 31 - __builtin_clz(l ^ r), uno = left[i][r], dos = right[i][l];
	return uno * dos % mod;
}
};

// Operation:
	int p;
	cin >> n >> p >> q;
	mod = p;
	vector<int> ar(n);
	for (i = 0; i < n; ++i) cin >> ar[i];
	DST t(a);
	vector<int> b((q >> 6) + 2);
	for (i = 0; i < (int)b.size(); ++i) cin >> b[i];
	int x = 0, l = 1, r = 1;
	for (i = 0; i < q; ++i) {
		if (i % 64 == 0) {
			l = (b[i / 64] + x) % n; r = (b[(i / 64) + 1] + x) % n;
		}
		else {
			l = (l + x) % n; r = (r + x) % n;
		}
		if (l > r) swap(l, r);
		x = t.get(l, r) + 1; x %= mod;
	}
	cout << x << '\n';

// 2-D Sparse Table:
https://www.codechef.com/problems/CENS20B

const int L = 10;
int st[N][N][L][L], ar[N][N], lg2[N];
int go(int x1, int y1, int x2, int y2) {
	++x2; ++y2; int a = lg2[x2 - x1], b = lg2[y2 - y1];
	return max({st[x1][y1][a][b], st[x2 - (1 << a)][y1][a][b], st[x1][y2 - (1 << b)][a][b], st[x2 - (1 << a)][y2 - (1 << b)][a][b]});
}
void make(int n, int m) {
    for (int i = 2; i < N; ++i) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) st[i][j][0][0] = ar[i][j];
	}
	for (int a = 0; a < L; ++a) {
		for (int b = 0; b < L; ++b) {
			if (a + b == 0) continue;
			for (int i = 0; i + (1 << a) <= n; ++i) {
				for (int j = 0; j + (1 << b) <= m; ++j) {
					if (!a) {
						st[i][j][a][b] = max(st[i][j][a][b - 1], st[i][j + (1 << (b - 1))][a][b - 1]);
					}
					else {
						st[i][j][a][b] = max(st[i][j][a - 1][b], st[i + (1 << (a - 1))][j][a - 1][b]);
					}
				}
			}
		}
	}
}
string s[N]; int l[N][N], u[N][N];
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
	cin >> n >> m;
	for (i = 0; i < n; ++i) {
		cin >> s[i];
	}
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			if (!j) l[i][j] = 1;
			else l[i][j] = 1 + (s[i][j - 1] <= s[i][j] ? l[i][j - 1] : 0);
		}
	}
	for (j = 0; j < m; ++j) {
		for (i = 0; i < n; ++i) {
			if (!i) u[i][j] = 1;
			else u[i][j] = 1 + (s[i - 1][j] <= s[i][j] ? u[i - 1][j] : 0);
		}
	}
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			int nw = 1, mnx = u[i][j], mny = l[i][j];
			for (int len = 1; len <= min(i, j); ++len) {
				mnx = min(mnx, u[i][j - len]);
				mny = min(mny, l[i - len][j]);
				if (min(mnx, mny) >= len + 1) ++nw;
				else break;
			}
			ar[i][j] = nw;
		}
	}
	make(n, m);
	cin >> q;
	while (q--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		x1--, y1--, x2--, y2--;
		int l = 1, r = min(x2 - x1 + 1, y2 - y1 + 1), ans = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			if (go(x1 + mid - 1, y1 + mid - 1, x2, y2) >= mid) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		cout << ans << '\n';
	}