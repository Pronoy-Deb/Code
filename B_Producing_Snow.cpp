#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const int64_t M = 1e9 + 7, N = 2e5 + 5;

template <typename T> struct vset {
	multiset<T> S; int64_t wlvl = 0;
	inline void insert(T v) { S.insert(v + wlvl); }
	inline auto erase(T v) {
        auto it = S.find(v + wlvl); return (it == S.end() ? it : S.erase(it));
    }
	inline void upal(T v) { wlvl += v; } // For Subtracting
	inline int64_t min() { return (S.empty() ? LLONG_MIN : *S.begin() - wlvl); }
    inline int64_t max() { return (S.empty() ? LLONG_MAX : *prev(S.end()) - wlvl); }
    inline bool empty() { return S.empty(); }
	inline int size() { return S.size(); }
};

void test(int32_t tc) {
    int64_t n; cin >> n;
    vector<int64_t> v(n);
    for (int i = 0; i < n; ++i) { cin >> v[i]; }
    vector<int64_t> t(n);
    for (int i = 0; i < n; ++i) { cin >> t[i]; }
    vset<int64_t> st;
    for (int i = 0; i < n; ++i) {
        st.insert(v[i]); st.upal(t[i]);
        int64_t tot = t[i] * st.size(), mn = st.min();
        while (!st.empty() && mn <= 0) {
            tot -= abs(mn); st.erase(mn); mn = st.min();
        }
        cout << tot << ' ';
    }
    cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    // cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}