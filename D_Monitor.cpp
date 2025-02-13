#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int M = 1e9 + 7, N = 2e5 + 5;

auto wmx1d(auto &v, int k) {
	int n = v.size(); vector<int> res(n - k + 1); deque<int> mq;
	for (int i = 0; i < n; ++i) {
		while (!mq.empty() && v[mq.back()] <= v[i]) mq.pop_back();
		mq.push_back(i); if (mq.front() <= i - k) mq.pop_front();
		if (i + 1 >= k) res[i - k + 1] = v[mq.front()];
	}
	return res;
}

auto wmx2d(auto &v, int k, int l) {
	int n = v.size(), m = v[0].size();
    vector<vector<int>> res(m - l + 1, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		auto tmp = wmx1d(v[i], l);
		for (int j = 0; j < m - l + 1; ++j) res[j][i] = tmp[j];
	}
	vector<vector<int>> ans(n - k + 1, vector<int>(m - l + 1));
	for (int j = 0; j < m - l + 1; ++j) {
		auto tmp = wmx1d(res[j], k);
		for (int i = 0; i < n - k + 1; ++i) ans[i][j] = tmp[i];
	}
	return ans;
}

auto wmn1d(auto &v, int k) {
	int n = v.size(); vector<int> res(n - k + 1); deque<int> mq;
	for (int i = 0; i < n; ++i) {
		while (!mq.empty() && v[mq.back()] >= v[i]) mq.pop_back();
		mq.push_back(i); if (mq.front() <= i - k) mq.pop_front();
		if (i + 1 >= k) res[i - k + 1] = v[mq.front()];
	}
	return res;
}

auto wmn2d(auto &v, int k, int l) {
	int n = v.size(), m = v[0].size();
    vector<vector<int>> res(m - l + 1, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		auto tmp = wmn1d(v[i], l);
		for (int j = 0; j < m - l + 1; ++j) res[j][i] = tmp[j];
	}
	vector<vector<int>> ans(n - k + 1, vector<int>(m - l + 1));
	for (int j = 0; j < m - l + 1; ++j) {
		auto tmp = wmn1d(res[j], k);
		for (int i = 0; i < n - k + 1; ++i) ans[i][j] = tmp[i];
	}
	return ans;
}

void test(int32_t tc) {
    ll n, m, k, q; cin >> n >> m >> k >> q;
    // vector<ll> ar(n); for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    vector<vector<int>> ar(n, vector<int>(m, -1));
    while (q--) {
        int r, c, v; cin >> r >> c >> v; ar[--r][--c] = v;
    }
    auto mx = wmx2d(ar, k, k), mn = wmn2d(ar, k, k);
    // ck(mx, mn);
    int r = mx.size(), c = mx[0].size(), ans = M;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (~mn[i][j]) ans = min(ans, mx[i][j]);
        }
    }
    cout << (ans == M ? -1 : ans) << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}