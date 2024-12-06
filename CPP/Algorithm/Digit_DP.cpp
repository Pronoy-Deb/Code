// Complexity: O()

vector<long long> L, R; long long dp[11][2][2][1001][91], k;
long long rec(int in, bool LLo, bool Lhi, int sum, int digsum) {
    if (in == R.size()) return (!sum && !digsum);
    auto &res = dp[in][LLo][Lhi][sum][digsum];
    if (~res) return res; res = 0;
    long long lo = (LLo ? 0 : L[in]), hi = (Lhi ? 9 : R[in]);
    for (long long i = lo; i <= hi; ++i) {
        bool NLhi = Lhi | (R[in] > i), NLlo = LLo | (i > L[in]);
        int Nsum = (sum * 10 + i) % k, Ndsum = (digsum + i) % k;
        res = (res + rec(in + 1, NLlo, NLhi, Nsum, Ndsum)) % M;
    }
    return res;
}

// Operation:
    memset(dp, -1, sizeof dp);
    string A, B; cin >> A >> B >> k;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    int mx = max(A.size(), B.size());
    while (A.size() < mx) A += '0';
    while (B.size() < mx) B += '0';
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    R.ansize(mx), L.ansize(mx);
    for (i = 0; i < mx; ++i) {
        R[i] = B[i] - '0'; L[i] = A[i] - '0';
    }
    if (k >= 100) {
        cout << 0 << '\n'; return;
    }
    cout << rec(0, 0, 0, 0, 0) << "\n";

// Problem: https://lightoj.com/problem/investigation

// 1. How many numbers less than 10^n(1 <= n, k <= 1000) having sum of digits equal to k?

long long n, k, dp[N][N];
long long rec(int in, int sum) {
    if (in == n) return sum == k;
    if (sum > k) return 0;
    auto &res = dp[in][sum];
    if (~res) return res; res = 0;
    for (int i = 0; i <= 9; ++i)
        res = (res + rec(in + 1, sum + i)) % M;
    return res;
}

// Operation:
    cin >> n >> k;
    memset(dp, -1, sizeof dp);
    cout << rec(0, 0);

// 2. How many n-digit(1 <= n, k <= 1000) numbers are divisible by k?

long long n, k, dp[N][N];
long long rec(int in, int rem) {
    if (in == n) return !rem;
    auto &res = dp[in][rem];
    if (~res) return res; res = 0;
    for (int i = 0; i <= 9; ++i) {
        if (!i and !in) continue;
        res = (res + rec(in + 1, (rem * 10 + i) % k)) % M;
    }
    return res;
}

// Operation:
    cin >> n >> k;
    memset(dp, -1, sizeof dp);
    cout << rec(0, 0);

// 3. What is the maximum sum of digits of a number less than or equal to n(1 <= n <= 10^100000)?

string s;
long long dp[N][2];
long long rec(int in, bool less) {
    if (in == s.size()) return 0;
    auto &res = dp[in][less];
    if (~res) return res; res = 0;
    int d = s[in] - '0', last = less ? 9 : d;
    for (int i = 0; i <= last; ++i)
        res = max(res, i + rec(in + 1, less | i < d));
    return res;
}

// Operation:
    cin >> s;
    memset(dp, -1, sizeof dp);
    cout << rec(0, false);

// 4. How many numbers are there in the range [l, r](1 <= l <= r <= 10^100000) that are divisible by 2 or 3 but not divisible by both?

string s;
long long dp[N][2][2][3];
long long rec(int in, bool less, int rem2, int rem3) {
    if (in == s.size()) return (!rem2) ^ (!rem3);
    auto &res = dp[in][less][rem2][rem3];
    if (~res) return res; res = 0;
    int d = s[in] - '0', last = less ? 9 : d;
    for (int i = 0; i <= last; ++i)
        res = (res + rec(in + 1, less | i < d, (rem2 * 10 + i) % 2, (rem3 * 10 + i) % 3)) % M;
    return res;
}
bool d3(auto &s) {
    int sum = 0; for(auto &i : s) sum += (i - 48);
    return !(sum % 3);
}

// Operation:
    string l, r; cin >> l >> r;
    s = r;
    memset(dp, -1, sizeof dp);
    a = rec(0, false, 0, 0);
    s = l;
    memset(dp, -1, sizeof dp);
    b = rec(0, false, 0, 0);
    cout << (((b - a + M) % M) + ((~(l.back() - '0') & 1) ^ d3(l))) % M;

// 5. How many numbers are there in the range [l, r](1 <= l <= r <= 10^100000) such that no consecutive digits are equal.

stirng s; long long dp[N][2][10][2];
long long rec(int in, bool less, int prev, bool L0) {
    if (in == s.size()) return 1;
    auto &res = dp[in][less][prev][L0];
    if (~res) return res; res = 0;
    int d = s[in] - '0', last = less ? 9 : d;
    for (int i = 0; i <= last; ++i) {
        if (!L0 and i == prev) continue;
        res = (res + rec(in + 1, less | i < d), i, L0 && !i) % M;
    }
    return res;
}

// Operation:
    string l, r; cin >> l >> r;
    s = r;
    memset(dp, -1, sizeof dp);
    a = rec(0, false, 0, false);
    s = l;
    memset(dp, -1, sizeof dp);
    b = rec(0, false, 0, false);
    bool fg = true; int sz = l.size();
    for (i = 1; i < sz; ++i) fg &= (l[i - 1] != l[i]);
    cout << (((b - a + M) % M) + fg) % M;

// 6. How many numbers are there in the range [l, r](1 <= l <= r <= 10^10000) such that each digit appears even number of times?

string s; long long dp[N][2][1025][2];
long long rec(int in, bool less, int mask, bool L0) {
    if (in == s.size()) return !mask;
    auto &res = dp[in][less][mask][l0];
    if (~res) return res; res = 0;
    int d = s[in] - '0', last = less ? 9 : d;
    for (int i = 0; i <= last; ++i) {
        if (!i) res = (res + rec(in + 1, less | i < d, mask ^ (!L0), L0)) % M;
        else res = (res + rec(in + 1, less | i < d, mask ^ (1 << i), true)) % M;
    }
    return res;
}

// Operation:
    string l, r; cin >> l >> r;
    s = r;
    memset(dp, -1, sizeof dp);
    a = rec(0, false, 0, false);
    s = l;
    memset(dp, -1, sizeof dp);
    b = rec(0, false, 0, false);
    int mask = 0; for (auto &e : l) mask ^= (1 << (e - '0'));
    cout << (((b - a + M) % M) + !mask) % M;


// YKW:

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define eb emplace_back
#define nl '\n'
#define deb(x) cerr << #x" = " << x << nl
#define in() ( { int a ; scanf("%d", &a); a; } )

const int N = 3e5 + 9;
const int mod = 1e9 + 7;

int pw[20][20], b[1 << 10][3000], cnt[1 << 10], dp[2][20][1 << 10][2520];
vector<int> v;
int yo(int i, int mask, int rem, int f) {
  if(i == -1) return pw[b[mask][rem]][cnt[mask]];
  int &ret = dp[f][i][mask][rem];
  if(ret != -1 && !f) return ret;
  int m = f ? v[i] : 9;
  int ans = 0;
  for(int k = 0; k <= m; k++) {
    ans += yo(i - 1, mask | (1 << k), (rem * 10 + k) % 2520, k == m ? f : 0);
    if(ans >= mod) ans -= mod;
  }
  if(!f) ret = ans;
  return ans;
}
int solve(ll n) {
  if(n == 0) return 0;
  v.clear();
  while(n) {
    v.eb(n % 10);
    n /= 10;
  }
  return yo(v.size() - 1, 0, 0, 1);
}
int32_t main() {
  memset(dp, -1, sizeof dp);
  for(int i = 1; i < 20; i++) {
    pw[i][0] = 1;
    for(int k = 1; k < 20; k++) pw[i][k] = pw[i][k - 1] * 1LL * i % mod;
  }
  for(int mask = 1; mask < (1 << 10); mask++) cnt[mask] = __builtin_popcount(mask) - (mask & 1);
  for(int mask = 1; mask < (1 << 10); mask++) {
    for(int rem = 0; rem < 2530; rem++) {
      for(int i = 1; i < 10; i++) if(mask >> i & 1) b[mask][rem] += rem % i == 0;
    }
  }
  int t;
  cin >> t;
  while(t--) {
    ll l, r;
    cin >> l >> r;
    cout << (solve(r) - solve(l - 1) + mod) % mod << nl;
  }
  return 0;
}