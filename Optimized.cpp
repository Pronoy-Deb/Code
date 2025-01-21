#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "Yes" : "No") << '\n'
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int32_t tc) {
    ll n, m; cin >> n >> m;
    multiset<ll> st; ll sum = 0;
    for (int i = 0; i < n; ++i) { ll a; cin >> a; sum += a; st.insert(a); }
    ll tot = 0;
    vector<ll> ar(m); for (int i = 0; i < m; ++i) { cin >> ar[i]; tot += ar[i]; }
    if (sum != tot) {
        ps(0); return;
    }
    for (int i = 0; i < m; ++i) {
        if (st.size() == 1 and (i != m - 1 or *st.begin() != ar[i])) {
            ps(0); return;
        }
        auto it = st.lower_bound(ar[i]);
        if (it != st.end() and *it == ar[i]) {
            st.erase(it);
        }
        else {
            // sum = 0;
            // bool ok = 0;
            while (st.size() > 1) {
                ll a = *st.begin();
                if (ar[i] - 2 * a <= 1) {
                    st.erase(st.begin());
                    auto it = st.find(ar[i] - a);
                    if (it != st.end()) {
                        st.erase(it);
                        break;
                    }
                    else st.insert(a);
                }
                ll b = *next(st.begin());
                if (b - a > 1) {
                    ps(0); return;
                }
                // sum += a + b;
                st.erase(st.begin()); st.erase(st.begin());
                st.insert(a + b);
            }
            // if (ok) continue;
            // if (!st.empty()) sum += *st.begin();
            // if (sum != ar[i]) {
            //     ps(0); return;
            // }
        }
    }
    ps(1);
    // cout << '\n';
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int32_t tc = 0, tt = 1;
    cin >> tt;
    while (tc++ < tt) test(tc);
    return 0;
}