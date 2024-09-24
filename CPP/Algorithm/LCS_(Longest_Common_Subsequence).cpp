// Complexity: O(n^2)
// To determine the length:
// Iterative Approach:

long long dp[N][N];
long long lcs(auto &s1, auto &s2) {
    int l1 = s1.size(), l2 = s2.size();
    for (int i = 1; i <= l1; ++i) {
		for (int j = 1; j <= l2; ++j)
            dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] + 1 : -1});
	}
    long long c = 0;
    while (l1 && l2) {
		if (s1[l1 - 1] == s2[l2 - 1]) {
			++c; --l1; --l2;
		}
        else {
			if (dp[l1 - 1][l2] > dp[l1][l2 - 1]) --l1;
			else --l2;
		}
	}
    return c;
}

// Recursive Approach (DP):

string s1, s2; long long dp[N][N];
long long lcs(int i, int j) {
    if (i < 0 || j < 0) return 0;
    auto &ans = dp[i][j]; if (~ans) return ans;
    ans = max(lcs(i - 1, j), lcs(i, j - 1));
    ans = max(ans, lcs(i - 1, j - 1) + (s1[i] == s2[j]));
    return ans;
}

// Calling:
    memset(dp, -1, sizeof dp);
    cin >> s1 >> s2;
    cout << lcs(s1.size() - 1, s2.size() - 1);

// To determine the subsequence:

long long dp[N][N];
auto lcs(auto &s1, auto &s2) {
    int l1 = s1.size(), l2 = s2.size();
    for (int i = 1; i <= l1; ++i) {
		for (int j = 1; j <= l2; ++j)
            dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] + 1 : -1});
	}
    string s;
    while (l1 && l2) {
		if (s1[l1 - 1] == s2[l2 - 1]) {
			s += s1[l1-1]; --l1; --l2;
		}
        else {
			if (dp[l1 - 1][l2] > dp[l1][l2 - 1]) --l1;
			else --l2;
		}
	}
    reverse(s.begin(), s.end()); return s;
}

// Operation:
    string s1, s2; cin >> s1 >> s2;
    cout << lcs(s1, s2);

// OR,

long long dp[N][N], mark[N][N], n, m; string s, s1;
long long lcs(int i, int j) {
    if (i == n or j == m) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (s[i] == s1[j]) {
        mark[i][j] = 1;
        return dp[i][j] = 1 + lcs(i + 1, j + 1);
    }
    else {
        long long a = lcs(i, j + 1), b = lcs(i + 1, j);
        if (a > b) mark[i][j] = 2;
        return dp[i][j] = max(a, b);
    }
}
void print(int i, int j) {
    if (i == n or j == m) return;
    if (mark[i][j] == 1) {
        cout << s[i]; print(i + 1, j + 1);
    }
    else if (mark[i][j] == 2) print(i, j + 1);
    else print(i + 1, j);
}

// Operation:
    cin >> s >> s1;
    n = s.size(); m = s1.size();
    memset(dp, -1, sizeof dp);
    lcs(0, 0);
    print(0, 0);

// All Substring Longest Common Subsequence:

#include<bits/stdc++.h>
using namespace std;

const int N = 2002;
int f[N][N], g[N][N];
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s, t; cin >> s >> t;
    int  n = s.size(), m = t.size();
    s = "#" + s;
    t = "#" + t;
    for (int i = 1; i <= m; ++i) f[0][i] = i;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i] == t[j]) {
                f[i][j] = g[i][j - 1];
                g[i][j] = f[i - 1][j];
            }
            else {
                f[i][j] = max(f[i - 1][j], g[i][j - 1]);
                g[i][j] = min(g[i][j - 1], f[i - 1][j]);
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = i, ans = 0; j <= m; ++j) {
            if (i > f[n][j]) ++ans;
            cout << ans << ' '; //lcs of s and t[i, j]
        }
        cout << '\n';
    }
    return 0;
}

// Bit LCS:

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
/* Bit-String Longest Common Subsequence Algorithm
O(nm/w)*/
const int N = 5e4 + 9, SIGMA = 26;
const int W = 62;
int M;
struct Bitset {
    long long u[N / W + 5];
    void clear() {
        memset(u, 0, sizeof(u));
    }
    void set(int x) {
        u[x / W] |= 1ll << (x % W);
    }
    Bitset operator | (const Bitset &r) const {
        Bitset s;
        for (int i = 0; i < M; ++ i) {
            s.u[i] = u[i] | r.u[i];
        }
        return s;
    }
    void yo(const Bitset &r) {
        for (int i = 0; i < M; ++ i) {
            u[i] = (u[i] ^ r.u[i]) & r.u[i];
        }
    }
    void sub(const Bitset &r) {
        for (int i = 0; i < M; ++ i) u[i] = r.u[i] - u[i];
        for (int i = 0; i < M; ++ i) if (u[i] < 0) {
                u[i] += 1ll << W;
                u[i + 1] --;
            }
    }
    void shl() {
        long long c = 1;
        for (long i = 0; i < M; ++ i) {
            u[i] <<= 1;
            u[i] |= c;
            c = u[i] >> W & 1;
            u[i] ^= c << W;
        }
    }
    int count() const {
        int c = 0;
        for (int i = 0; i < M; ++ i) {
            c += __builtin_popcountll(u[i]);
        }
        return c;
    }
} row, bs[SIGMA], x;
int main() {
    for (int i = 0; i < SIGMA; ++i) bs[i].clear();
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    for (int i = 0; i < n; ++ i) {
        bs[s[i] - 'a'].set(i);
    }
    M = n / W + (n % W != 0);
    row.clear();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < M; ++j) {
            x.u[j] = row.u[j] | bs[t[i] - 'a'].u[j];
        }
        row.shl();
        row.sub(x);
        row.yo(x);
        //printf("%d\n", row.count()); //lcs of prefix of t and whole s
    }
    cout << row.count() << '\n';
    return 0;
}
//https://www.spoj.com/problems/LCS0/

// Cyclic LCS:

#include<bits/stdc++.h>
using namespace std;

const int N = 2010;
/*Cyclic Longest Common Subsequence
maximum of lcs(any cyclic shift of s, any cyclic shift of t)
O(nm)*/
int dp[N * 2][N], from[N * 2][N];
int yo(string s, string t) {
    int n = s.size(), m = t.size();
    auto eq = [&](int a, int b) {
        return s[(a - 1) % n] == t[(b - 1) % m];
    };
    dp[0][0] = from[0][0] = 0;
    for (int i = 0; i <= n * 2; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = 0;
            if (j && dp[i][j - 1] > dp[i][j]) {
                dp[i][j] = dp[i][j - 1];
                from[i][j] = 0;
            }
            if (i && j && eq(i, j) && dp[i - 1][j - 1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                from[i][j] = 1;
            }
            if (i && dp[i - 1][j] > dp[i][j]) {
                dp[i][j] = dp[i - 1][j];
                from[i][j] = 2;
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret = max(ret, dp[i + n][m]);
        // re-root
        int x = i + 1, y = 0;
        while (y <= m && from[x][y] == 0) ++y;
        for (; y <= m && x <= n * 2; ++x) {
            from[x][y] = 0, --dp[x][m];
            if (x == n * 2) break;
            for (; y <= m; ++y) {
                if (from[x + 1][y] == 2) break;
                if (y + 1 <= m && from[x + 1][y + 1] == 1) {
                    ++y;
                    break;
                }
            }
        }
    }
    return ret;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s, t;
    cin >> s >> t;
    cout << yo(s, t) << '\n';
    return 0;
}