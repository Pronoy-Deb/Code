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
const ll M = 1e9 + 7, N = 1e8;

// bitset<N> ip;
// void pre() {
// 	ip[2] = true; for (int i = 3; i < N; i += 2) ip[i] = true;
//     for (long long i = 3, j; (j = i * i) < N; i += 2) {
//         for (; ip[i] && j < N; j += (i << 1)) ip[j] = false;
//     }
// }

// auto pfac(long long n) {
//     // map<long long, long long> mp;
//     int a = 0;
//     while (~n & 1) {
//         a++;
//         if(a > 2) return false;
//         n >>= 1;
//     }
//     for (long long i = 3; i * i <= n; i += 2) {
//         while (!(n % i)) {
//             a++;
//             if(a > 2) return false;
//             n /= i;
//         }
//     }
//     if (n > 2) a++;
//     return (a == 2);
//     // return mp;
// }
bitset<N> ip; vector<long long> pri;
void pre() {
	pri.push_back(2);
	for (long long i = 3; i < N; i += 2) {
		if (!ip[i]) {
			pri.push_back(i);
			for (long long j = i * i; j < N; j += (i << 1)) ip[j] = 1;
		}
	}
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n);
    pre();
    set<int> st;
    for (i = 0; i < pri.size(); ++i) {
        for(j = 0; j < pri.size() and pri[i] * pri[j] < N; ++j) {
            st.insert(pri[i] * pri[j]);
        }
        // c += pfac(i);
    }
    cout << st.size();
    cout << '\n';
    ck(*prev(st.end()));
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}