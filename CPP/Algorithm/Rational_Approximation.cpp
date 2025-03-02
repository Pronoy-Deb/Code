#include <bits/stdc++.h>
using namespace std;

/**
Given n and a real number x >= 0, returns the closest rational approximation p/q s.t. p, q <= n.
It will obey that |p/q - x| is minimum for p, q <= n
Time: O(log n)
**/

using ld = long double;
pair<int64_t, int64_t> approximate(ld x, int64_t n)
{
    int64_t LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX;
    ld y = x;
    while (1)
    {
        int64_t lim = min(P ? (n - LP) / P : inf, Q ? (n - LQ) / Q : inf),
           a = (int64_t)floor(y), b = min(a, lim),
           NP = b * P + LP, NQ = b * Q + LQ;
        if (a > b)
        {
            // If b > a/2, we have a semi-convergent that gives us a
            // better approximation; if b = a/2, we *may* have one.
            // Return {P, Q} here for a more canonical approximation.
            return (abs(x - (ld)NP / (ld)NQ) < abs(x - (ld)P / (ld)Q)) ? make_pair(NP, NQ) : make_pair(P, Q);
        }
        if (abs(y = 1 / (y - (ld)a)) > 3 * n)
        {
            return {NP, NQ};
        }
        LP = P;
        P = NP;
        LQ = Q;
        Q = NQ;
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
        long double x;
        cin >> x;
        int64_t n = 1e9;
        auto ans = approximate(x, n);
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}
// https://official.contest.yandex.ru/opencupXVIII/contest/5457/problems/E?lang=en