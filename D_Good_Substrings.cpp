#include <bits/stdc++.h>
using namespace std;
#define ck(n) cout << #n " = " << n << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define pe(c) for (auto& i : c) cout << i << ' '; cout << '\n'
#define pp(c) for (auto& [f, s] : c) cout << f << " : " << s << '\n'
#define pr(c) for (auto& i:c) {for(auto& j:i) cout<<j<<' '; cout<<'\n';}
const int M = 1e9 + 7, N = 1505;
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
    modint<MOD> * inv() const { return pow(MOD - 2); }
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.* inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.* inv(); }
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
mint pre[N], pre1[N];
void fhs(string& s, int base) {
    int n = s.size(); mint p = 1;
    for (int i = 0; i < n; ++i) {
        if (base == 29) pre[i + 1] = (pre[i] + (p * (s[i] - 95)));
        else pre1[i + 1] = (pre1[i] + (p * (s[i] - 95)));
        p = (p * base);
    }
}
mint mmi(mint base, int pow = M - 2) {
    mint ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base);
        base = (base * base); pow >>= 1;
    }
    return ans;
}
mint inv[N], inv1[N], pw[N];
void power(int base) {
    pw[0] = inv[0] = inv1[0] = 1;
    for (int i = 1; i < N; ++i) {
        pw[i] = (pw[i - 1] * base);
        if (base == 29) inv[i] = mmi(pw[i]);
        else inv1[i] = mmi(pw[i]);
    }
}
void Accepted() {
    string s, r; cin >> s >> r;
    int n = s.size(), k; cin >> k; fhs(s, 29); fhs(s, 31); power(29); power(31);
    set<pair<mint, mint>> st;
    for (int i = 0; i < n; ++i) {
        int c = (r[s[i] - 'a'] == '0');
        if (c <= k) st.emplace(((((pre[i + 1] - pre[i]))) * inv[i]), ((((pre1[i + 1] - pre1[i]))) * inv1[i]));
        for (int j = i + 1; j < n; ++j) {
            c += (r[s[j] - 'a'] == '0');
            if (c <= k) st.emplace(((((pre[j + 1] - pre[i]))) * inv[i]), ((((pre1[j + 1] - pre1[i]))) * inv1[i]));
        }
    }
    cout << st.size();
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cin.exceptions(ios::badbit | ios::failbit);
    // int tc; cin >> tc; while (tc--)
    Accepted();
    return 0;
}