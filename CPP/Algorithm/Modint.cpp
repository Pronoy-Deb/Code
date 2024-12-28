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
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.pow(M - 2); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.pow(M - 2); }
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


// OR,


struct mint {
	const static int M = 998244353;
	ll v = 0;
	mint() {}
	mint(long long v) { this->v = (v % M + M) % M; }
	mint operator+(const mint &o) const { return v + o.v; }
	mint &operator+=(const mint &o) {
		v = (v + o.v) % M;
		return *this;
	}
	mint operator*(const mint &o) const { return v * o.v; }
	mint operator-(const mint &o) const { return v - o.v; }
	mint &operator-=(const mint &o) {
		mint t = v - o.v;
		v = t.v;
		return *this;
	}
	mint operator^(int y) const {
		mint r = 1, x = v;
		for (y <<= 1; y >>= 1; x = x * x)
			if (y & 1) r = r * x;
		return r;
	}
	mint inv() const {
		assert(v);
		return *this ^ M - 2;
	}
	friend istream &operator>>(istream &s, mint &v) {
		return s >> v.v;
		return s;
	}
	friend ostream &operator<<(ostream &s, const mint &v) { return s << v.v; }
	mint operator/(mint o) { return *this * o.inv(); }
};