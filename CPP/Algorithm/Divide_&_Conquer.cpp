https://cses.fi/problemset/task/1647/

int64_t L[N], R[N], aa[N], ans[N]; pair<int, int> qr[N];
inline int64_t op(int64_t l, int64_t r) { return min(l, r); }
void dnq(int l, int r, auto &queries) {
    if (queries.empty()) return;
    if (l == r) {
        for (int i : queries) ans[i] = aa[l]; return;
    }
    int m = (l + r) >> 1; L[m] = aa[m];
    for (int i = m - 1; i >= l; --i) L[i] = op(aa[i], L[i + 1]);
    R[m + 1] = aa[m + 1];
    for (int i = m + 2; i <= r; ++i) R[i] = op(R[i - 1], aa[i]);
    vector<int> lq, rq;
    for (int i : queries) {
        int s = qr[i].first, e = qr[i].second;
        if (s <= m && m < e) {
            ans[i] = op(op(L[s], aa[m]), R[e]); continue;
        }
        if (e <= m) lq.push_back(i);
        else rq.push_back(i);
    }
    dnq(l, m, lq); dnq(m + 1, r, rq);
}

// Operation:
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> aa[i];
    for (int i = 0; i < q; ++i) {
        cin >> qr[i].first >> qr[i].second;
        --qr[i].first, --qr[i].second;
    }
    vector<int> ind(q); iota(ind.begin(), ind.end(), 0);
    dnq(0, n - 1, ind);
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';

https://codeforces.com/problemset/problem/1400/E

vector<int> aa(N);
int rec(int l, int r) {
    if (l > r) return 0;
    int mn = *min_element(aa.begin() + l, aa.begin() + r + 1), idx = -1;
    for (int i = l; i <= r; ++i) {
        aa[i] -= mn; if (!aa[i]) idx = i;
    }
    return min(rec(l, idx - 1) + rec(idx + 1, r) + mn, r - l + 1);
}

// Operation:
    int64_t n; cin >> n;
    for (int i = 0; i < n; ++i) { cin >> aa[i]; }
    cout << rec(0, n - 1) << '\n';

// * Divide and Conquer Optimization
// * Must satisfy : Opt(i,j) <= Opt(i,j+1)

const int64_t INF = 1e17;
int64_t DW[N], D[N], W[N], n;

int64_t cost(int64_t l, int64_t r) {
    int64_t num = DW[r - 1] - DW[l - 1];
    int64_t denom = (D[n] - D[r - 1]) * (W[r - 1] - W[l - 1]);
    return num - denom;
}
vector<int64_t> dp_before(N), dp_cur(N);
void compute(int64_t l, int64_t r, int64_t optl, int64_t optr) {
    if (l > r) return;
    int64_t mid = (l + r) >> 1, best = INF, opt = -1;
    for (int64_t k = optl; k <= min(mid, optr); ++k) {
        int64_t cur = (k ? dp_before[k - 1] : 0) + cost(k, mid);
        if (cur < best) best = cur, opt = k;
    }
    dp_cur[mid] = best;
    compute(l, mid - 1, optl, opt); compute(mid + 1, r, opt, optr);
}

// Operation:
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> W[i] >> D[i];
    int64_t totD = 0;
    for (i = n; i >= 1; --i) {
        totD += D[i]; DW[i] = totD * W[i];
    }
    for (i = 1; i <= n; ++i) {
        DW[i] += DW[i - 1]; D[i] += D[i - 1]; W[i] += W[i - 1];
    }
    for (i = 1; i <= n; ++i) dp_before[i] = cost(1, i);
    for (i = 2; i <= 3; ++i) {
        compute(1, n + 1, 1, n + 1); dp_before = dp_cur;
    }
    cout << dp_before[n + 1];

// Problem: https://szkopul.edu.pl/problemset/problem/ovRIpLFK3IhyFPjnVXeZtGxH/site/?key=statement

// OR,

const int N = 4010, inf = 1e9;

int sc() {
	int c = getchar();
	int x = 0;
	int neg = 0;
	for(; ((c < 48 || c > 57) && c != '-'); c = getchar());
	if(c == '-') {
		neg = 1;
		c = getchar();
	}
	for(; c > 47 && c < 58; c = getchar()) {
		x = (x << 1) + (x << 3) + c - 48;
	}
	if(neg) x = -x;
	return x;
}

// Divide 1,2,3...n people in k consecutive parts so that sum of cost of each individual part is minimum
int a[N][N], c[N][N], dp[810][N]; // dp[i][j]=minimum cost for dividing [1...j] into i parts
int cost(int i, int j) {
	// assert(i <= j);
	return c[j][j] - c[i - 1][j] - c[j][i - 1] + c[i - 1][i - 1];
}
void yo(int i, int l, int r, int optl, int optr) {
	if(l > r) return;
	int mid = (l + r) / 2;
	dp[i][mid] = inf; // for maximum cost change it to 0
	int opt = -1;
	for(int k = optl; k <= min(mid - 1, optr); k++) {
		int c = dp[i - 1][k] + cost(k + 1, mid);
		if(c < dp[i][mid]) { // for maximum cost just change < to > only and rest of the algo should not be changed
			dp[i][mid] = c;
			opt = k;
		}
	}
	// for opt[1..j] <= opt[1...j+1]
	if (opt == -1) {
    // if we can't divide into k parts, then go right
		yo(i, mid + 1, r, optl, optr);
		return;
	}
	yo(i, l, mid - 1, optl, opt);
	yo(i, mid + 1, r, opt, optr);

	// for opt[1...j] >= opt[1...j+1]
	// yo(i, l, mid-1, opt, optr);
	// yo(i, mid+1, r, optl, opt);

}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int i, j, k, n, m;
	n = sc();
	k = sc();
	for(i = 1; i <= n; i++) for(j = 1; j <= n; j++) a[i][j] = sc();
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			c[i][j] = a[i][j] + c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];
		}
	}
  for(i = 1; i <= k; i++) {
    for (j = 1; j <= n; j++) {
      dp[i][j] = inf;
    }
  }
	for(i = 1; i <= n; i++) dp[1][i] = cost(1, i);
	for(i = 2; i <= k; i++) yo(i, 1, n, 1, n);
	cout << dp[k][n] / 2 << endl;
	return 0;
}
// https://codeforces.com/contest/321/problem/E