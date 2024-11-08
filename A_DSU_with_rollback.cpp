#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;
class DSU {
  private:
	vector<int> par, sz; int c;
    vector<pair<int&, int>> history;
  public:
	DSU(int n) : par(n + 1), sz(n + 1, 1), c(n) { iota(par.begin(), par.end(), 0); }
	int get(int i) {
        return (par[i] == i ? i : get(par[i]));
    }
    int cc() { return c; }
	void uni(int a, int b) {
		a = get(a); b = get(b); if (a == b) return;
		if (sz[a] < sz[b]) { swap(a, b); }
        history.push_back({c, c});
        history.push_back({sz[a], sz[a]});
        history.push_back({par[b], par[b]});
		par[b] = a; sz[a] += sz[b]; --c;
	}
	int ss() { return history.size(); }
	void rlbk(int until) {
		while (ss() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};
void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> q;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    DSU dsu(n);
    vector<int> ss;
    while (q--) {
        string op; cin >> op;
        if (op == "union") {
            cin >> a >> b; dsu.uni(a, b);
            cout << dsu.cc() << '\n';
        }
        else if (op == "persist")
            ss.push_back(dsu.ss());
        else {
            if (ss.empty()) continue;
            dsu.rlbk(ss.back());
            ss.pop_back();
            cout << dsu.cc() << '\n';
        }
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}