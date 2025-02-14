https://codeforces.com/problemset/problem/432/D

auto prefix(auto &s) {
    int n = s.size(); vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        j += (s[i] == s[j]); pi[i] = j;
    }
    return pi;
}
auto pref_occur(auto &pi) {
    int n = pi.size(); vector<int> cnt(n + 1);
    for (int i = 0; i < n; ++i) ++cnt[pi[i]];
    for (int l = n; l > 0; --l) {
        cnt[pi[l - 1]] += cnt[l]; ++cnt[l];
    }
    return cnt;
}

// Operation:
    string s; cin >> s;
    auto pi = prefix(s), pre = pref_occur(pi);
    vector<int> res;
    for (int i = s.size(); i > 0; i = pi[i - 1]) res.push_back(i);
    reverse(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto x : res) cout << x << ' ' << pre[x] << '\n';

// OR,

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define eb emplace_back
#define ll long long
#define nl '\n'
#define deb(x) cerr << #x " = " << x << nl
#define in() ({ int a ; scanf("%d",&a); a; })

const int N = 1e5 + 9;
const int mod = 1e9 + 7;

vector<int> prefix_function(string &s)
{
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
int aut[N][26];
void compute_automaton(string s)
{
    s += '#';
    int n = (int)s.size();
    vector<int> pi = prefix_function(s);
    for (int i = 0; i < n; i++)
    {
        for (int c = 0; c < 26; c++)
        {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i - 1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
vector<vector<int>> dp;
int n, m;
string s, p;
int yo(int i, int j)
{
    if (i == n)
        return (j == m);
    int &ret = dp[i][j];
    if (ret != -1)
        return ret;
    ret = 0;
    if (s[i] == '?')
    {
        for (int c = 0; c < 26; c++)
        {
            ret = max(ret, yo(i + 1, aut[j][c]));
        }
    }
    else
        ret = yo(i + 1, aut[j][s[i] - 'a']);
    ret += j == m;
    return ret;
}
/// change '?'s in string s so that the number of occurrences of p is maximized
int32_t main()
{
    char ch[N];
    scanf("%s", ch);
    s = ch;
    scanf("%s", ch);
    p = ch;
    compute_automaton(p);
    n = s.size();
    m = p.size();
    dp.resize(n, vector<int>(m + 1, -1));
    cout << yo(0, 0) << nl;
    return 0;
}
