// Complexity: O(n)
// Application: Used to determine the number of palindromes in a string.

auto man(auto &s) {
    string t = "$#"; for (auto &c : s) t += c + string("#");
    t += '^'; int n = t.size(), l = 0, r = 0; vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (t[i - p[i]] == t[i + p[i]]) ++p[i];
        if (i + p[i] > r) {
            l = i - p[i]; r = i + p[i];
        }
    }
    return p;
}

// OR,

#include <bits/stdc++.h>
using namespace std;

struct Manacher
{
    vector<int> p[2];
    // p[1][i] = (max odd length palindrome centered at i) / 2 [floor division]
    // p[0][i] = same for even, it considers the right center
    // e.g. for s = "abbabba", p[1][3] = 3, p[0][2] = 2
    Manacher(string s)
    {
        int n = s.size();
        p[0].resize(n + 1);
        p[1].resize(n);
        for (int z = 0; z < 2; z++)
        {
            for (int i = 0, l = 0, r = 0; i < n; i++)
            {
                int t = r - i + !z;
                if (i < r)
                    p[z][i] = min(t, p[z][l + t]);
                int L = i - p[z][i], R = i + p[z][i] - !z;
                while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
                    p[z][i]++, L--, R++;
                if (R > r)
                    l = L, r = R;
            }
        }
    }
    bool is_palindrome(int l, int r)
    {
        int mid = (l + r + 1) / 2, len = r - l + 1;
        return 2 * p[len % 2][mid] + len % 2 >= len;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    Manacher M(s);
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        cout << 2 * M.p[1][i] + 1 << ' ';
        if (i + 1 < n)
            cout << 2 * M.p[0][i + 1] << ' ';
    }
    cout << '\n';
    return 0;
}
// https://judge.yosupo.jp/problem/enumerate_palindromes