// Sparse Table:

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

int t[N][18], a[N];
void build(int n) {
  for(int i = 1; i <= n; ++i) t[i][0] = a[i];
  for(int k = 1; k < 18; ++k) {
    for(int i = 1; i + (1 << k) - 1 <= n; ++i) {
      t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
    }
  }
}

int query(int l, int r) {
  int k = 31 - __builtin_clz(r - l + 1);
  return min(t[l][k], t[r - (1 << k) + 1][k]);
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  build(n);
  int q;
  cin >> q;
  while(q--) {
    int l, r;
    cin >> l >> r;
    ++l;
    ++r;
    cout << query(l, r) << '\n';
  }
  return 0;
}

// Disjoint Sparse Table: O(nlogn) preprocessing, O(1) query

#include<bits/stdc++.h>
using namespace std;
int mod = 1e9 + 7;

struct DST {
vector<vector<int>> left, right; int k, n;
DST(vector<int> & a) {
    n = (int)a.size(); k = log2(n) + 2;
    left.assign(k + 1, vector<int>(n));
    right.assign(k + 1, vector<int>(n));
    for(int j = 0; (1 << j) <= n; ++j) {
        int mask = (1 << j) - 1, nw = 1; // neutral
        for(int i = 0; i < n; ++i) {
            nw = 1LL * nw * a[i] % mod; // prefix value
            left[j][i] = nw;
            if((i & mask) == mask) nw = 1; // neutral
        }
        nw = 1; // neutral
        for(int i = n - 1; i >= 0; --i) {
            nw = 1LL * nw * a[i] % mod; // prefix value
            right[j][i] = nw;
            if((i & mask) == 0) nw = 1; // neutral
        }
    }
}
int query(int l, int r) {
    if(l == r) return left[0][l];
    int i = 31 - __builtin_clz(l ^ r), uno = left[i][r], dos = right[i][l];
    return 1LL * uno * dos % mod;
}
};

int32_t main() {
    int tc; cin >> tc;
    while (tc--) {
        int n, p, q; cin >> n >> p >> q;
        mod = p; vector<int> a(n);
        for(int i = 0; i < n; ++i) cin >> a[i];
        DST t(a); vector<int> b((q >> 6) + 2);
        for(int i = 0; i < (int)b.size(); ++i) cin >> b[i];
        int x = 0, l = 1, r = 1;
        for(int i = 0; i < q; ++i) {
            if(i % 64 == 0) {
                l = (b[i / 64] + x) % n;
                r = (b[(i / 64) + 1] + x) % n;
            }
            else {
                l = (l + x) % n; r = (r + x) % n;
            }
            if(l > r) swap(l, r);
            x = t.query(l, r) + 1; x %= mod;
        }
        cout << x << '\n';
    }
    return 0;
}

// https://www.codechef.com/problems/SEGPROD

// Sparse Table 2D:

#include<bits/stdc++.h>
using namespace std;

const int N = 505, LG = 10;

int st[N][N][LG][LG];
int a[N][N], lg2[N];

int yo(int x1, int y1, int x2, int y2) {
  x2++;
  y2++;
  int a = lg2[x2 - x1], b = lg2[y2 - y1];
  return max(
         max(st[x1][y1][a][b], st[x2 - (1 << a)][y1][a][b]),
         max(st[x1][y2 - (1 << b)][a][b], st[x2 - (1 << a)][y2 - (1 << b)][a][b])
       );
}

void build(int n, int m) { // 0 indexed
  for (int i = 2; i < N; i++) lg2[i] = lg2[i >> 1] + 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      st[i][j][0][0] = a[i][j];
    }
  }
  for (int a = 0; a < LG; a++) {
    for (int b = 0; b < LG; b++) {
      if (a + b == 0) continue;
      for (int i = 0; i + (1 << a) <= n; i++) {
        for (int j = 0; j + (1 << b) <= m; j++) {
          if (!a) {
            st[i][j][a][b] = max(st[i][j][a][b - 1], st[i][j + (1 << (b - 1))][a][b - 1]);
          } else {
            st[i][j][a][b] = max(st[i][j][a - 1][b], st[i + (1 << (a - 1))][j][a - 1][b]);
          }
        }
      }
    }
  }
}

string s[N];
int l[N][N], u[N][N];

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!j) l[i][j] = 1;
      else l[i][j] = 1 + (s[i][j - 1] <= s[i][j] ? l[i][j - 1] : 0);
    }
  }
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      if (!i) u[i][j] = 1;
      else u[i][j] = 1 + (s[i - 1][j] <= s[i][j] ? u[i - 1][j] : 0);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int nw = 1, mnx = u[i][j], mny = l[i][j];
      for (int len = 1; len <= min(i, j); len++) {
        mnx = min(mnx, u[i][j - len]);
        mny = min(mny, l[i - len][j]);
        if (min(mnx, mny) >= len + 1) nw++;
        else break;
      }
      a[i][j] = nw;
    }
  }
  build(n, m);
  int q;
  cin >> q;
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--, y1--;
    x2--;
    y2--;
    int l = 1, r = min(x2 - x1 + 1, y2 - y1 + 1), ans = 0;
    while (l <= r) {
      int mid = l + r >> 1;
      if (yo(x1 + mid - 1, y1 + mid - 1, x2, y2) >= mid) ans = mid, l = mid + 1;
      else r = mid - 1;
    }
    cout << ans << '\n';
  }
  return 0;
}
// https://www.codechef.com/problems/CENS20B