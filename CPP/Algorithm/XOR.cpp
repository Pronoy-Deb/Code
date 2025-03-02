// Xor from 1 to n: O(1)

int64_t xor(int64_t n) {
    int rem = n % 4;
    return !rem ? n : (rem == 1) ? 1 : (rem == 2) ? n + 1 : 0;
}

// Static Range XOR Query: O(n * logn)
// Note: 1-based indexing
https://cses.fi/problemset/task/1650

int64_t pxr[N], aa[N];
void pre() {
	for (int i = 1; i < N; ++i) pxr[i] = pxr[i - 1] ^ aa[i - 1];
}
int64_t xr(int l, int r) { return pxr[r] ^ pxr[l - 1]; }

// OR,
    cin >> n >> q;
    ll aa[n + 1][32];
    for (int i = 0; i < 32; ++i) aa[0][i] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a;
        for (j = 0; j < 32; ++j) aa[i][j] = aa[i - 1][j] + (bool)(a & (1 << j));
    }
    while (q--) {
        cin >> a >> b; c = 0;
        for (int i = 0; i < 32; ++i) {
            d = aa[b][i] - aa[a - 1][i];
            if (d & 1) c |= (1 << i);
        }
        cout << c << '\n';
    }

// Maximum XOR Subarray: O(n)
https://cses.fi/problemset/task/1655

const int L = 30;
int64_t trie[N * L][2], c = 0;
void up(int64_t x) {
    int64_t nd = 0;
    for (int i = L; i >= 0; --i) {
        int64_t y = x >> i & 1;
        if (!trie[nd][y]) trie[nd][y] = ++c;
        nd = trie[nd][y];
    }
}
int64_t get(int64_t x) {
    int64_t ans = 0, nd = 0;
    for (int i = L; i >= 0; --i) {
        int64_t y = x >> i & 1;
        if (trie[nd][y ^ 1]) {
            nd = trie[nd][y ^ 1]; ans += (1 << i);
        }
        else nd = trie[nd][y];
    }
    return ans;
}
void reset(int n) { for (int i = 0; i <= n; ++i) trie[i][0] = trie[i][1] = 0; }

// Operation:
    cin >> n;
    int64_t xr = 0, mx = 0; up(xr);
    for (int i = 0; i < n; ++i) {
        int64_t x; cin >> x; xr ^= x; up(xr);
        mx = max(get(xr), mx);
    }
    cout << mx;

// Maximum XOR Subsequence: O(n)

// NOT CORRECTED YET

// int64_t mxxor(auto &v) {
//     int n = v.size(), ind = 0;
//     for (int i = 31; i >= 0; --i) {
//         int64_t mx = LLONG_MIN, mxind = ind;
//         for (int j = ind; j < n; ++j) {
//             if (v[j] & (1 << i) && v[j] > mx) {
//                 mxind = j; mx = v[j];
//             }
//         }
//         if (mx == LLONG_MIN) continue;
//         swap(v[ind], v[mxind]); mxind = ind;
//         for (int j = 0; j < n; ++j) {
//             if (v[j] & (1 << i) && j != mxind) v[j] ^= mx;
//         }
//         ++ind;
//     }
//     int64_t ans = 0; for (int i = 0; i < n; ++i) ans ^= v[i];
//     return ans;
// }

// XOR Segment Tree:
https://codeforces.com/contest/1654/problem/F

int64_t aa[N];
struct XORSegmentTree {
    // the length of the array should be 2^LOG for some LOG
    vector<int64_t> t[4 * N]; // O(LOG 2^LOG) memory
    int64_t lazy[4 * N];
    XORSegmentTree() {
        for (int i = 0; i < 4 * N; i++) {
            t[i].clear();
            lazy[i] = 0;
        }
    }
    // b = 0, e = 2^LOG - 1
    // O(LOG 2^LOG)
    void build(int n, int b, int e) {
    lazy[n] = 0;
    t[n].clear();
    if (b == e) {
        t[n].push_back(aa[b]);
        return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    int len = e - b + 1;
    // t[n][i] = sum of aa[p ^ i] over all b <= p <= e
    t[n].resize(len);
    for (int i = 0; i < len; i++) {
        if (i < (len >> 1)) t[n][i] = t[l][i] + t[r][i];
        else t[n][i] = t[r][i - (len >> 1)] + t[l][i - (len >> 1)];
    }
    }
    // add x to aa[i], basically the change occurs for all t[n][i] where n is a candidate node
    // so we just create a lazy array to remember the change for each node
    // O(LOG)
    void upd(int n, int b, int e, int i, int64_t x) {
    if (b > i || e < i) return;
    lazy[n] += x;
    if (b == e && b == i) {
        return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    upd(l, b, mid, i, x);
    upd(r, mid + 1, e, i, x);
    }
    // layer = LOG - 1
    // return sum of aa[p ^ x] over all i <= p <= j
    // O(LOG)
    int64_t query(int n, int b, int e, int i, int j, int x, int layer) {
    if (i > j or b > j or e < i) return 0;
    if (b >= i and e <= j) return lazy[n] + (layer == -1 ? t[n][0] : t[n][x & ((1 << layer + 1) - 1)]);
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    if (~x >> layer & 1) return query(l, b, mid, i, j, x, layer - 1) + query(r, mid + 1, e, i, j, x, layer - 1);
    else {
        int i1 = i, j1 = min(mid, j), i2 = max(i, mid + 1), j2 = j;
        return query(r, mid + 1, e, mid + 1 + i1 - b, mid + 1 + j1 - b, x, layer - 1) +
        query(l, b, mid, b + i2 - (mid + 1), b + j2 - (mid + 1), x, layer - 1);
    }
    }
}t;
mt19937_64 ran(chrono::high_resolution_clock::now().time_since_epoch().count());
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int k = 17, n = (1 << k);
  for (int i = 0; i < n; i++) {
    aa[i] = ran() % 1000000000;
  }
  t.build(1, 0, n - 1);
  int q = 1000;
  while (q--) {
    int l = ran() % n, r = ran() % (n - l) + l, x = ran() % (1 << k);
    int z = ran() % n, add = ran() % 100;
    t.upd(1, 0, n - 1, z, add);
    aa[z] += add;
    int64_t sum = 0;
    for (int i = l; i <= r; i++) {
      sum += aa[i ^ x];
    }
    int64_t res = t.query(1, 0, n - 1, l, r, x, k - 1);
    cout << sum << ' ' << res << '\n';
    assert(sum == res);
  }
  return 0;
}

// XOR Equation:

const int N = 55, mod = 1000000003;
int k, Z, dp[N][2][2]; vector<int64_t> A;
// par = parity of the number of kth bits which are on
// f = if we have offed any kth bit
int yo(int i, int par, int f) {
    if (i == -1)
        return par == Z and f;
    int &ret = dp[i][par][f];
    if (ret != -1)
        return ret;
    ret = 0;
    if (Aa[i] >> k & 1)
    {
        ret += 1LL * yo(i - 1, par ^ 1, f) * ((Aa[i] - (1LL << k) + 1) % mod) % mod; // keep it on
        ret %= mod;
        // make it off
        if (f)
        {
            ret += 1LL * yo(i - 1, par, 1) * ((1LL << k) % mod) % mod;
            ret %= mod;
        }
        else
        {
            ret += yo(i - 1, par, 1);
            ret %= mod;
        }
    }
    else
    {
        ret += 1LL * yo(i - 1, par, f) * ((Aa[i] + 1) % mod) % mod;
        ret %= mod;
    }
    return ret;
}

// number of solutions of the equation x0 xor x1 xor ... x(n - 1) = x s.t. 0 <= xi <= ai
// O(n * log(MAX))
int solve(vector<int64_t> a, int64_t x, int K)
{
    int n = a.size();
    k = K;
    bool allzero = true;
    for (int i = 0; i < n; ++i)
        allzero &= aa[i] == 0;
    if (allzero)
        return x == 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        int64_t x = aa[i];
        cnt += x >> k & 1;
    }
    memset(dp, -1, sizeof dp);
    A = a;
    Z = x >> k & 1;
    int ans = yo(n - 1, 0, 0);
    if (cnt % 2 == Z)
    {
        for (int i = 0; i < n; ++i)
        {
            int64_t &x = aa[i];
            if (x >> k & 1)
                x ^= 1 << k;
        }
        if (x >> k & 1)
            x ^= 1 << k;
        ans += solve(a, x, k - 1);
        ans %= mod;
    }
    return ans;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int64_t x;
    while (cin >> n >> x and n)
    {
        vector<int64_t> a(n);
        for (int i = 0; i < n; ++i)
            cin >> aa[i];
        cout << solve(a, x, 30) << '\n';
    }
    return 0;
}
// http://poj.org/problem?id=3986
// idea: https://www.hackerrank.com/challenges/stonegame/editorial

// All Possible Perfect Matching XOR Values:

#include <bits/stdc++.h>
using namespace std;

const int N = 1030;

int aa[N][N], p[N], n, vis[N];
void yo(int cur)
{
    if (vis[cur])
        return;
    vis[cur] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int nxt = cur ^ aa[i][p[i]] ^ aa[j][p[j]] ^ aa[i][p[j]] ^ aa[j][p[i]];
            swap(p[i], p[j]);
            yo(nxt);
            swap(p[i], p[j]);
        }
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int cur = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> aa[i][j];
                if (i == j)
                    p[i] = i, cur ^= aa[i][i];
            }
        }
        memset(vis, 0, sizeof vis);
        yo(cur);
        for (int i = 0; i < N; i++)
            if (vis[i])
                cout << i << ' ';
        cout << '\n';
    }
    return 0;
}
// https://www.codechef.com/problems/CHEFLST

// XOR Equation Arbitary Range:

const int N = 55, mod = 1000000003;
int k, Z, dp[N][2][2];
vector<int64_t> A;
// par = parity of the number of kth bits which are on
// f = if we have offed any kth bit
int yo(int i, int par, int f)
{
    if (i == -1)
    {
        return par == Z and f;
    }
    int &ret = dp[i][par][f];
    if (ret != -1)
        return ret;
    ret = 0;
    if (Aa[i] >> k & 1)
    {
        ret += 1LL * yo(i - 1, par ^ 1, f) * ((Aa[i] - (1LL << k) + 1) % mod) % mod; // keep it on
        ret %= mod;
        // make it off
        if (f)
        {
            ret += 1LL * yo(i - 1, par, 1) * ((1LL << k) % mod) % mod;
            ret %= mod;
        }
        else
        {
            ret += yo(i - 1, par, 1);
            ret %= mod;
        }
    }
    else
    {
        ret += 1LL * yo(i - 1, par, f) * ((Aa[i] + 1) % mod) % mod;
        ret %= mod;
    }
    return ret;
}

// number of solutions of the equation x0 xor x1 xor ... x(n - 1) = x s.t. 0 <= xi <= ai
// O(n * log(MAX))
int solve(vector<int64_t> a, int64_t x, int K)
{
    int n = a.size();
    k = K;
    bool allzero = true;
    for (int i = 0; i < n; i++)
    {
        allzero &= aa[i] == 0;
    }
    if (allzero)
        return x == 0;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        int64_t x = aa[i];
        cnt += x >> k & 1;
    }
    memset(dp, -1, sizeof dp);
    A = a;
    Z = x >> k & 1;
    int ans = yo(n - 1, 0, 0);
    if (cnt % 2 == Z)
    {
        for (int i = 0; i < n; i++)
        {
            int64_t &x = aa[i];
            if (x >> k & 1)
                x ^= 1 << k;
        }
        if (x >> k & 1)
            x ^= 1 << k;
        ans += solve(a, x, k - 1);
        ans %= mod;
    }
    return ans;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int64_t x;
    while (cin >> n >> x and n)
    {
        vector<int64_t> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> aa[i];
        }
        cout << solve(a, x, 30) << '\n';
    }
    return 0;
}
// http://poj.org/problem?id=3986
// idea: https://www.hackerrank.com/challenges/stonegame/editorial