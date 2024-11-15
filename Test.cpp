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
long long ar[N], nfg[N], n;
void pre() {
    // set<pair<int, int>> st;
	map<int, vector<int>> mp;
	for (int i = 0; i < n; ++i) {
		mp[]
	}
    // stack<long long> sk;
    // for (int i = n - 1; i >= 0; --i) {
    //     while(!sk.empty() && ar[i] >= ar[sk.top()]) {
    //         // nfg[sk.top()] = i;
	// 		sk.pop();
    //     }
    //     if (!sk.empty()) nfg[i] = sk.top();
	// 	else nfg[i] = -1;
    //     sk.push(i);
    // }
    // while (!sk.empty()) {
    //     nfg[sk.top()] = -1; sk.pop();
    // }
}
void test(int tc) {
	ll p = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
	cin >> n;
	for (i = 0; i < n; ++i) { cin >> ar[i]; }
	pre();
	pn(nfg, n);
	// cout << '\n';
}

signed main() {
	cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
	int tc = 0, t = 1;
	cin >> t;
	while (tc < t) test(++tc);
	return 0;
}