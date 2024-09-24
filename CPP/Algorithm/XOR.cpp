// Xor from 1 to n:
// Complexity: O(1)

long long xor (auto n) {
    int rem = n % 4;
    return !rem ? n : (rem == 1) ? 1
                  : (rem == 2)   ? n + 1
                                 : 0;
}

    // XOR Equation:

    const int N = 55,
              mod = 1000000003;
int k, Z, dp[N][2][2];
vector<long long> A;
// par = parity of the number of kth bits which are on
// f = if we have offed any kth bit
int yo(int i, int par, int f)
{
    if (i == -1)
        return par == Z and f;
    int &ret = dp[i][par][f];
    if (ret != -1)
        return ret;
    ret = 0;
    if (A[i] >> k & 1)
    {
        ret += 1LL * yo(i - 1, par ^ 1, f) * ((A[i] - (1LL << k) + 1) % mod) % mod; // keep it on
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
        ret += 1LL * yo(i - 1, par, f) * ((A[i] + 1) % mod) % mod;
        ret %= mod;
    }
    return ret;
}

// number of solutions of the equation x0 xor x1 xor ... x(n - 1) = x s.t. 0 <= xi <= ai
// O(n * log(MAX))
int solve(vector<long long> a, long long x, int K)
{
    int n = a.size();
    k = K;
    bool allzero = true;
    for (int i = 0; i < n; ++i)
        allzero &= a[i] == 0;
    if (allzero)
        return x == 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        long long x = a[i];
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
            long long &x = a[i];
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
    long long x;
    while (cin >> n >> x and n)
    {
        vector<long long> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
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

int a[N][N], p[N], n, vis[N];
void yo(int cur)
{
    if (vis[cur])
        return;
    vis[cur] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int nxt = cur ^ a[i][p[i]] ^ a[j][p[j]] ^ a[i][p[j]] ^ a[j][p[i]];
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
                cin >> a[i][j];
                if (i == j)
                    p[i] = i, cur ^= a[i][i];
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

#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <iterator>
#include <complex>
#include <iomanip>
#include <cassert>
using namespace std;

const int N = 55, mod = 1000000003;

int k, Z;
int dp[N][2][2];
vector<long long> A;
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
    if (A[i] >> k & 1)
    {
        ret += 1LL * yo(i - 1, par ^ 1, f) * ((A[i] - (1LL << k) + 1) % mod) % mod; // keep it on
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
        ret += 1LL * yo(i - 1, par, f) * ((A[i] + 1) % mod) % mod;
        ret %= mod;
    }
    return ret;
}

// number of solutions of the equation x0 xor x1 xor ... x(n - 1) = x s.t. 0 <= xi <= ai
// O(n * log(MAX))
int solve(vector<long long> a, long long x, int K)
{
    int n = a.size();
    k = K;
    bool allzero = true;
    for (int i = 0; i < n; i++)
    {
        allzero &= a[i] == 0;
    }
    if (allzero)
        return x == 0;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        long long x = a[i];
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
            long long &x = a[i];
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
    long long x;
    while (cin >> n >> x and n)
    {
        vector<long long> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cout << solve(a, x, 30) << '\n';
    }
    return 0;
}
// http://poj.org/problem?id=3986
// idea: https://www.hackerrank.com/challenges/stonegame/editorial