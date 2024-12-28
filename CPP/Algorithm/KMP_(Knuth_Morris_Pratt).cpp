// Complexity: O(|p| + |s|)
// Application: Used to find all occurrences of a pattern in a text in linear time
lightoj.com/problem/substring-frequency

auto kmp(auto &str, auto &pat) {
    int pl = pat.size(), sl = str.size(), sz = max(pl, sl) + 5, pi[sz], now = pi[0] = -1, match = 0;
    for (int i = 1; i < pl; ++i) {
        while (now != -1 && pat[now + 1] != pat[i]) now = pi[now];
        if (pat[now + 1] == pat[i]) ++now; pi[i] = now;
    }
    now = -1; vector<int> ind;
    for (int i = 0; i < sl; ++i) {
        while (now != -1 && pat[now + 1] != str[i]) now = pi[now];
        if (pat[now + 1] == str[i]) ++now;
        // match += (now == pl - 1);
        if(now == pl - 1) ind.emplace_back(i - pl + 1);  // To determine the indices
    }
    return ind;
}

// OR,

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9; // >= k^n

// creates a cyclic string of length k^n that contains every length n string as a substring. alphabet = [0, k - 1]
// O(k^n)
int ans[N], aux[N];
int de_bruijn(int k, int n)
{ // returns size (k^n)
    if (k == 1)
    {
        ans[0] = 0;
        return 1;
    }
    for (int i = 0; i < k * n; i++)
    {
        aux[i] = 0;
    }
    int sz = 0;
    function<void(int, int)> db = [&](int t, int p)
    {
        if (t > n)
        {
            if (n % p == 0)
            {
                for (int i = 1; i <= p; i++)
                {
                    ans[sz++] = aux[i];
                }
            }
        }
        else
        {
            aux[t] = aux[t - p];
            db(t + 1, p);
            for (int i = aux[t - p] + 1; i < k; i++)
            {
                aux[t] = i;
                db(t + 1, t);
            }
        }
    };
    db(1, 1);
    return sz;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k, n;
    cin >> k >> n;
    int len = de_bruijn(k, n);
    for (int i = 0; i < len; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}

// Hashing Approach:

const ll M = 9223372036854775783ll, N = 1e6 + 5;
__int128_t cfh(auto &s, int base = 31) {
    __int128_t sz = s.size(), tmp = 0, pow = 1;
    for (int i = 0; i < sz; ++i) {
        tmp = (tmp + ((s[i] - 'a') * pow) % M) % M;
        pow = (pow * base) % M;
    }
    return tmp;
}
__int128_t mmi(__int128_t base) {
    base %= M; __int128_t ans = 1, pow = M - 2;
    while (pow) {
        if (pow & 1) ans = (ans * base) % M;
        base = (base * base) % M; pow >>= 1;
    }
    return ans;
}
__int128_t hs[N], pw[N], inv[N]; int m; string r;
void pre(__int128_t p = 31) {
    pw[0] = inv[0] = 1; __int128_t inv_p = mmi(p);
	for (int i = 1; i < N; ++i) {
        pw[i] = (pw[i - 1] * p) % M;
        inv[i] = (inv[i - 1] * inv_p) % M;
	}
}
void pre1(__int128_t p = 31) {
    for (int i = 0; i < m; ++i)
        hs[i + 1] = (hs[i] + (pw[i] * (r[i] - 'a')) % M) % M;
}

void test(int32_t tc) {
    ll n, c; cin >> n >> m >> c;
    vector<ll> ar(m); for (int i = 0; i < m; ++i) { cin >> ar[i]; }
    string s; cin >> s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    ll sz = s.size(), hsh = cfh(s); bool ok = 0;
    while (n--) {
        cin >> r; transform(r.begin(), r.end(), r.begin(), ::tolower); pre1();
        ll tot = 0;
        for (int i = sz; !ok and i <= m; ++i) {
            ll hash = ((hs[i] - hs[i - sz] + M) % M * inv[i - sz]) % M;
            if (hash == hsh and tot < c) tot += ar[i - sz];
            if (tot >= c) ok = 1;
        }
    }
    cout << "Case " << tc << ": " << (ok? "Yes" : "No") << '\n';
}

// Operation:
    pre();