// Complexity: O(|p| + |s|)
// Application: Used to find all occurrences of a pattern in a text in linear time
// vector<long long> ind;

long long pi[N]; // N = p.size()
long long kmp(auto &str, auto &pat) {
    long long now = pi[0] = -1, pl = pat.size();
    for (int i = 1; i < pl; ++i) {
        while (now != -1 && pat[now + 1] != pat[i]) now = pi[now];
        if (pat[now + 1] == pat[i]) ++now; pi[i] = now;
    }
    long long ans = 0, sl = str.size(); now = -1;
    for (int i = 0; i < sl; ++i) {
        while (now != -1 && pat[now + 1] != str[i]) now = pi[now];
        if (pat[now + 1] == str[i]) ++now;
        if (now == pl - 1) ++ans;
        // if(now == pl-1) ind.emplace_back(i-pl+1);  // To determine the indices
    }
    return ans;
}

// Problem: lightoj.com/problem/substring-frequency

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