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
const ll M = 1e9 + 7, N = 1e7 + 200;

long long pri[N], spf[N];
void pre() {
    for (int i = 2, c = 0; i < N; ++i) {
        if (!spf[i]) pri[c++] = spf[i] = i;
        for (int j = 0, k; (k = i * pri[j]) < N; ++j) {
            spf[k] = pri[j];
            if (spf[i] == spf[k]) break;
        }
    }
}
long long modmul(long long x, long long y, long long m) {
    long long res = __int128(x) * y % m; return res;
    // long long res = x * y - (long long)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
}
long long bex(long long x, long long n, long long m) {
    long long res = 1 % m;
    while (n) {
        if (n & 1) res = modmul(res, x, m);
        x = modmul(x, x, m); n >>= 1;
    }
    return res;
}
bool ip(long long n) {
	if (n < 2 || (~n & 1) || !(n % 3)) return (n == 2 || n == 3);
    if (n < N) return spf[n] == n;
    long long s = 0, r = n - 1;
    while (~r & 1) { r >>= 1; ++s; }
    for (int i = 0; pri[i] < n && pri[i] < 32; ++i) {
        long long c = bex(pri[i], r, n);
        for (int j = 0; j < s; ++j) {
            long long d = modmul(c, c, n);
            if (d == 1 && c != 1 && c != (n - 1)) return false;
            c = d;
        }
        if (c != 1) return false;
    }
    return true;
}

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cout << "Case #" << tc << ": ";
    cin >> n;
    for(i=5;i<=n;i+=2) {
        if(ip(i) and ip(i - 2)) a++;
    }
    cout << a + (n > 4);
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    pre();
    // pn(pri, 20);
    // ck(pri);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}