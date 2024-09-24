#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define pc cout << "Case " << tc << ": "
#ifdef LOCAL
#include "def.h"
#else
#define ck(...) 
#endif
const ll M = 1e9 + 7, N = 2e5 + 5;
ll n;
vector<ll> v(N);
ll vis[N];
set<ll> st[N];
auto cnt() {
    ll i, j;
    // set<ll> st;
    for (i = 0; i < n;++i){
        if(vis[i] == 2) continue;
        // c++;
        if(vis[i] == 0) 
        st.insert(i);
        // vis3[i] = 1;
        for (j = i + v[i]; j < n; j += v[j]){
            // if(st.find(j) != st.end())
            //     break;
            vis[j]++;
            if (j + v[j] >= n)
                break;
            // st.insert(j);
        }
    }
    // return c;
}
void test(int tc) {
    ll b = 0, d = 0, i = 0, j = 0, k = 0, m = 0, q = 0;
    cin >> n;
    for (i = 0; i < n; ++i) { cin >> v[i]; }
    cnt();
    b = st.size();
    ck(b, st);
    for (i = 0; i < n;++i) {
        // if(st.find(i) != st.end()) {
            if((i + v[i] < n and vis[i + v[i]] == 2) or i + v[i] >= n)
                cout << b << ' ';
            else
                cout << b + 1 << ' ';
        // }
        // else {
        //     if((i + v[i] < n and vis[i + v[i]] == 2) or i + v[i] >= n)
        //         cout << b << ' ';
        //     else
        //         cout << b + 1 << ' ';
        // }
        // cout << b + ((vis2[i] and !vis3[i]) or i==0) << ' ';
        // vis[i] = 0;
        // vis2[i] = 0;
        // vis3[i] = 0;
    }
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit|cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}