#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
const ll M = 1e9 + 7, N = 1e5 + 5;
int par[N], sz[N], n;
void make() {
    for (int i = 1; i <= n; ++i) {
        par[i] = i; sz[i] = 1;
    }
}
int get(int nd) {
    return par[nd] = (par[nd] == nd ? nd : get(par[nd]));
}
void uni(int a, int b) {
    a = get(a); b = get(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    }
}
bool same(int a, int b) { return get(a) == get(b); }
void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    map<string, int> mp;
    pair<int, int> ar[n];
    for (i = 0; i < n; ++i) {
        string s; cin >> s;
        auto it = mp.find(s);
        if(it == mp.end()) {
            mp[s] = ++c;
            a = c;
        }
        else a = it->second;
        cin >> s;
        it = mp.find(s);
        if(it == mp.end()) {
            mp[s] = ++c;
            b = c;
        }
        else b = it->second;
        ar[i] = {a, b};
    }
    // auto it = mp.find("Lucy");
    // if(it == mp.end()) {
    //     while(n--) cout << "0\n";
    //     return;
    // }
    // a = it->second;
    n = c;
    make();
    for(auto &[f, s] : ar) {
        if(!same(f, s)) uni(f, s);
        cout << sz[get(f)] << '\n';
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}