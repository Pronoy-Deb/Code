// Subsequence Generation:
// Note: Number of subsequences of a string : 2^n - 1
// Bitmasking Approach: O(2^n)  // n = inp.size()

vector<string> res;
void sseq(auto &inp) {
    int sz = inp.size(), n = (1 << sz);
    for (int i = 1; i < n; ++i) {
        string sub; int j = 0, hi = __builtin_popcount(i);
        while (hi) {
            if (i & (1 << j)) { sub += inp[j]; --hi; } ++j;
        }
        res.emplace_back(sub);
    }
}

// Recursive Approach: O(2^n)  // n = inp.size()

vector<string> res;
auto sseq(auto &inp, auto &sub, auto i) {
    if (i == inp.size()) {
        if (!sub.empty()) res.emplace_back(sub);
        return;
    }
    sseq(inp, sub, i + 1);  // Not considering the i-th character
    sub += inp[i];
    sseq(inp, sub, i + 1);  // Considering the i-th character
    sub.pop_back();  // Backtracking
}

Calling: string inp = "abc", sub; sseq(inp, sub, 0);

// Number of Subsequences having Product at least K:

#include<bits/stdc++.h>
using namespace std;

const int N = 1010, mod = 1e9 + 7, SQ = sqrt(mod) + 1;

int a[N], k;
int dp1[N][SQ], dp2[N][SQ];
int mul_back(int i, int p) {
  if (i <= 0) return p >= 1;
  int &ret = dp1[i][p];
  if (ret != -1) return ret;
  ret = mul_back(i - 1, p);
  ret += mul_back(i - 1, p / a[i]);
  if (ret >= mod) ret -= mod;
  return ret;
}
int mul_front(int i, int p) {
  if (i <= 0) return p <= k;
  int &ret = dp2[i][p];
  if (ret != -1) return ret;
  ret = mul_front(i - 1, p);
  if (1LL * a[i] * p < SQ) ret += mul_front(i - 1, p * a[i]);
  else ret += mul_back(i - 1, k / (1LL * p * a[i]));
  if (ret >= mod) ret -= mod;
  return ret;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  memset(dp1, -1, sizeof dp1);
  memset(dp2, -1, sizeof dp2);
  int n; cin >> n >> k;
  --k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    ans = (ans + ans) % mod;
  }
  cout << (ans - mul_front(n, 1) + mod) % mod << '\n';
  return 0;
}
// https://codeforces.com/group/NOwIbqv33y/contest/307527/problem/J