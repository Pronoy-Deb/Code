{
	// Place your snippets for cpp here. Each snippet is defined under a snippet name and has a prefix, body and
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the
	// same ids are connected.
	// Example:
	"Print to console": {
		"prefix": "te",
		"body": [
			// 		"console.log('$1');",
			// 		"$2"
			"#include <bits/stdc++.h>",
			"using namespace std;",
			"#define ll long long",
			"#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\\n'",
			"#define ps(b) cout << (b ? \"YES\" : \"NO\") << '\\n'",
			"#ifdef LOCAL",
			"#include \"def.h\"",
			"#else""#define ck(...)",
			"#endif",
			"const ll M = 1e9 + 7, N = 2e5 + 5;",
			"",
			"void test(int tc) {",
			"\tll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;",
			"\tcin >> n;",
			"\tvector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }",
			"\t$0",
			"\tcout << '\\n';",
			"}",
			"",
			"signed main() {",
			"\tcin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);",
			"\tint tc = 0, t = 1;",
			"\tcin >> t;",
			"\twhile (tc < t) test(++tc);",
			"\treturn 0;",
			"}",
		],
		"description": "Log output to console",
	},

	"Print to console1": {
		"prefix": "mi",
		"body": [
			"template <const int64_t MOD>",
			"struct modint {",
			"\tint64_t val; modint() = default; modint(int64_t value) : val(value % MOD) { if (val < 0) val += MOD; }",
			"\tinline modint<MOD> operator+(modint<MOD> other) const { int64_t c = this->val + other.val; return modint<MOD>(c >= MOD ? c - MOD : c); }",
			"\tinline modint<MOD> operator-(modint<MOD> other) const { int64_t c = this->val - other.val; return modint<MOD>(c < 0 ? c + MOD : c); }",
			"\tinline modint<MOD> operator*(modint<MOD> other) const { int64_t c = (__int128_t)this->val * other.val % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }",
			"\tinline modint<MOD> &operator+=(modint<MOD> other) { this->val += other.val; if (this->val >= MOD) this->val -= MOD; return *this; }",
			"\tinline modint<MOD> &operator-=(modint<MOD> other) { this->val -= other.val; if (this->val < 0) this->val += MOD; return *this; }",
			"\tinline modint<MOD> &operator*=(modint<MOD> other) { this->val = (__int128_t)this->val * other.val % MOD; if (this->val < 0) this->val += MOD; return *this; }",
			"\tinline modint<MOD> operator-() const { return modint<MOD>(this->val ? MOD - this->val : 0); }",
			"\tmodint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }",
			"\tmodint<MOD> inv() const { return pow(MOD - 2); }",
			"\tinline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }",
			"\tinline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }",
			"\tinline bool operator==(modint<MOD> other) const { return val == other.val; }",
			"\tinline bool operator!=(modint<MOD> other) const { return val != other.val; }",
			"\tinline bool operator<(modint<MOD> other) const { return val < other.val; }",
			"\tinline bool operator>(modint<MOD> other) const { return val > other.val; }",
			"};",
			"template <int64_t MOD> modint<MOD> operator*(int64_t val, modint<MOD> n) { return modint<MOD>(val) * n; }",
			"template <int64_t MOD> modint<MOD> operator*(int32_t val, modint<MOD> n) { return modint<MOD>(val % MOD) * n; }",
			"template <int64_t MOD> istream &operator>>(istream &in, modint<MOD> &n) { int64_t val; in >> val; n = modint<MOD>(val); return in; }",
			"template <int64_t MOD> ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.val; }",
			"using mint = modint<M>;",
		],
		// "description": "Log output to console",
	}
}