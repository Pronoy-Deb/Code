#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 3e5 + 5;

struct aho_corasick_static {
    int ct[N], link[N], psz = 0; map<char, int> to[N];
    void clear() {
        for (int i = 0; i < psz; ++i) {
            ct[i] = 0; link[i] = -1; to[i].clear();
        }
        psz = 1; link[0] = -1; ct[0] = 0;
    }
    aho_corasick_static() { psz = N - 2; clear(); }
    void add(string &s) {
        int u = 0;
        for (char c : s) {
            if (!to[u].count(c)) to[u][c] = psz++; u = to[u][c];
        }
        ++ct[u];
    }
    void push_links() {
        queue<int> Q; Q.push(0); link[0] = -1;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (auto it : to[u]) {
                int v = it.second, j = link[u]; char c = it.first;
                while (j != -1 && !to[j].count(c)) j = link[j];
                link[v] = (~j ? to[j][c] : 0);
                ct[v] += ct[link[v]]; Q.push(v);
            }
        }
    }
    int cnt(string &p) {
        int u = 0, ans = 0;
        for (char c : p) {
            while (u != -1 && !to[u].count(c)) u = link[u];
            u = (~u ? to[u][c] : 0); ans += ct[u];
        }
        return ans;
    }
};

struct aho {
    vector<string> li[20]; aho_corasick_static ac[20];
    void clear() {
        for (int i = 0; i < 20; ++i) {
            li[i].clear(); ac[i].clear();
        }
    }
    aho() { clear(); }
    void add(string &s) {
        int pos = 0;
        for (int l = 0; l < 20; ++l) {
            if (li[l].empty()) { pos = l; break; }
        }
        li[pos].push_back(s); ac[pos].add(s);
        for (int bef = 0; bef < pos; ++bef) {
            ac[bef].clear();
            for (string &s2 : li[bef]) {
                li[pos].push_back(s2); ac[pos].add(s2);
            }
            li[bef].clear();
        }
        ac[pos].push_links();
    }
    // sum of occurrences of all patterns in this string s
    int cnt(string &s) {
        int ans = 0;
        for (int l = 0; l < 20; ++l) ans += ac[l].cnt(s);
        return ans;
    }
};
aho ins, rem;

void test(int32_t tc) {
    int64_t n; cin >> n;
    while (n--) {
        int ty; string s; cin >> ty >> s;
        if (ty == 1) ins.add(s);
        else if (ty == 2) rem.add(s);
        else cout << ins.cnt(s) - rem.cnt(s) << endl;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}