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
const ll M = 1e15 + 37, N = 2e5 + 5;

template <const int64_t MOD>
struct modint {
    int64_t val; modint() = default; modint(int64_t value) : val(value % MOD) { if (val < 0) val += MOD; }
    inline modint<MOD> operator+(modint<MOD> other) const { int64_t c = this->val + other.val; return modint<MOD>(c >= MOD ? c - MOD : c); }
    inline modint<MOD> operator-(modint<MOD> other) const { int64_t c = this->val - other.val; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> operator*(modint<MOD> other) const { int64_t c = (__int128_t)this->val * other.val % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> &operator+=(modint<MOD> other) { this->val += other.val; if (this->val >= MOD) this->val -= MOD; return *this; }
    inline modint<MOD> &operator-=(modint<MOD> other) { this->val -= other.val; if (this->val < 0) this->val += MOD; return *this; }
    inline modint<MOD> &operator*=(modint<MOD> other) { this->val = (__int128_t)this->val * other.val % MOD; if (this->val < 0) this->val += MOD; return *this; }
    inline modint<MOD> operator-() const { return modint<MOD>(this->val ? MOD - this->val : 0); }
    modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
    modint<MOD> inv() const { return pow(MOD - 2); }
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
    inline bool operator==(modint<MOD> other) const { return val == other.val; }
    inline bool operator!=(modint<MOD> other) const { return val != other.val; }
    inline bool operator<(modint<MOD> other) const { return val < other.val; }
    inline bool operator>(modint<MOD> other) const { return val > other.val; }
};
template <int64_t MOD> modint<MOD> operator*(int64_t val, modint<MOD> n) { return modint<MOD>(val) * n; }
template <int64_t MOD> modint<MOD> operator*(int32_t val, modint<MOD> n) { return modint<MOD>(val % MOD) * n; }
template <int64_t MOD> istream &operator>>(istream &in, modint<MOD> &n) { int64_t val; in >> val; n = modint<MOD>(val); return in; }
template <int64_t MOD> ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.val; }
using mint = modint<M>;

mint hs[N]; int n; string s;
mint bex(mint base, long long pow = M - 2) {
    mint ans = 1;
    while (pow) {
        if (pow & 1) ans *= base; base *= base; pow >>= 1;
    }
    return ans;
}
void pre() {
    mint pw = 1;
    for (int i = 0; i < n; ++i) {
        hs[i + 1] = hs[i] + (pw * (s[i] - 95)); pw *= 29;
    }
}

void test(int tc) {
    ll o = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n >> s;
    pre(); set<mint> st;
    for (int i = 0; i < n - 1; ++i)
        st.emplace((hs[i] * bex(29, 2)) + (hs[n] - hs[i + 2]));
    cout << st.size();
    cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    int tc = 0, t = 1;
    cin >> t;
    while (tc < t) test(++tc);
    return 0;
}