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
const ll M = 1e9 + 7, N = 2e5 + 5;

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}



// #include <sys/resource.h>
// void set_stack_size(rlim_t stack_size) {
//   struct rlimit rl;
//   int result = getrlimit(RLIMIT_STACK, &rl);
//   if (result == 0) {
//     if (rl.rlim_cur < stack_size) {
//       rl.rlim_cur = stack_size;
//       result = setrlimit(RLIMIT_STACK, &rl);
//     }
//   }
// }


// set_stack_size(1024 * 1024 * 1024); // 1 GB