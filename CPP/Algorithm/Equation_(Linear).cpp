// Complexity: O(1)

1. Solution of the equation: a*x = c;  // One unknown variable

long double sol(auto a, auto c) {
	return c / (1.0 * a);
}

2. Solution of the equations: a1*x + b1*y = c1; a2*x + b2*y = c2;  // Two unknown variables

long double a1, b1, c1, a2, b2, c2;
void sol(auto &x, auto &y) {
	x = (b2 * c1 - b1 * c2) / (1.0 * (a1 * b2 - a2 * b1));
	y = (c2 * a1 - c1 * a2) / (1.0 * (a1 * b2 - a2 * b1));
}

// Operation:
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    long double x, y; sol(x, y);

3. Solution of the equations: a1*x + b1*y + c1*z = d1;
    a2*x + b2*y + c2*z = d2; a3*x + b3*y + c3*z = d3;  // Three unknown variables

long double co[3][4];  // 3 x 4 matrix of co-efficients
auto det(auto (&mat)[3][3]) {
	return (mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]));
}
void sol(auto &x, auto &y, auto &z) {
	long double d[3][3]={{co[0][0],co[0][1],co[0][2]},{co[1][0],co[1][1],co[1][2]},{co[2][0],co[2][1],co[2][2]}};
	long double d1[3][3]={{co[0][3],co[0][1],co[0][2]},{co[1][3],co[1][1],co[1][2]},{co[2][3],co[2][1],co[2][2]}};
	long double d2[3][3]={{co[0][0],co[0][3],co[0][2]},{co[1][0],co[1][3],co[1][2]},{co[2][0],co[2][3],co[2][2]}};
	long double d3[3][3]={{co[0][0],co[0][1],co[0][3]},{co[1][0],co[1][1],co[1][3]},{co[2][0],co[2][1],co[2][3]}};
	long double D = det(d), D1 = det(d1), D2 = det(d2), D3 = det(d3);
	if (D) {
		x = D1 / (1.0 * D); y = D2 / (1.0 * D); z = D3 / (1.0 * D);
	}
}

// Operation:
    for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; ++j) cin >> co[i][j];
	}
	long double x = 0, y = 0, z = 0; sol(x, y, z);
	if (!x && !y && !z) cout << "Infinite solution or No solution";

// Gaussian Elimination Method:
// Complexity: O(n^3)
// Use: Used to solve n number of equations in order to find out n unknown values
// const int N = 10;

long double co[N][N+1]; int n;
auto sol() {
	vector<long double> val(n);
	for (int k = 0; k < n; ++k) {  // loop of forward elimination
		int i_max = k; long double v_max = co[i_max][k];
		for (int i = k + 1; i < n; ++i) {
			if (abs(co[i][k]) > v_max) {
				v_max = co[i][k]; i_max = i;
			}
		}
		if (!co[k][i_max]) return val;
		if (i_max != k) {
			for (int i = 0; i <= n; ++i) swap(co[k][i], co[i_max][i]);
		}
		for (int i = k + 1; i < n; ++i) {
			long double f = co[i][k] / co[k][k];
			for (int j = k + 1; j <= n; ++j) co[i][j] -= co[k][j] * f;
			co[i][k] = 0;
		}
	}
	for (int i = n - 1; i >= 0; --i) {  // loop of backward substitution
		val[i] = co[i][n];
		for (int j = i + 1; j < n; ++j) val[i] -= co[i][j] * val[j];
		val[i] = val[i] / co[i][i];
	}
	return val;
}

// Operation:
	cin >> n;  // Number of equations / unknown variables
	for (i = 0; i < n; ++i) {
		for (j = 0; j <= n; ++j) cin >> co[i][j];
	}
	auto ans = sol();  // all values are 0 if no solution exist
	for(auto &i : ans) cout << i << '\n';

// Number of Solutions of an Equation MITM:

#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

template <const int32_t MOD>
struct modint {
  int32_t value;
  modint() = default;
  modint(int32_t value_) : value(value_) {}
  inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
  inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
  inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
  inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
  inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
  inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
  modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
  modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
  inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
  inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<MOD> other) const { return value == other.value; }
  inline bool operator != (modint<MOD> other) const { return value != other.value; }
  inline bool operator < (modint<MOD> other) const { return value < other.value; }
  inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

using poly = vector<mint>;

mint eval(poly a, mint x) {
  mint ans = 0, p = 1;
  for (mint b : a) {
    ans += p * b;
    p *= x;
  }
  return ans;
}
poly operator + (poly a, poly b) {
  if (a.size() < b.size()) a.resize(b.size(), 0);
  for (int i = 0; i < b.size(); i++) {
    a[i] += b[i];
  }
  return a;
}
poly operator - (poly a, poly b) {
  if (a.size() < b.size()) a.resize(b.size(), 0);
  for (int i = 0; i < b.size(); i++) {
    a[i] -= b[i];
  }
  return a;
}
poly operator * (poly a, poly b) {
  vector<mint> r(a.size() + b.size() - 1, 0);
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      r[i + j] += a[i] * b[j];
    }
  }
  return r;
}


vector<pair<long long, int>> get(vector<long long> a) {
  int n = a.size();
  vector<pair<long long, int>> ans;
  for (int mask = 0; mask < (1 << n); mask++) {
    long long add = 0; int x = 1;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        add += a[i];
        x = -x;
      }
    }
    ans.push_back({add, x});
  }
  return ans;
}
// (x + n)(x + n - 1)...(x + n - k + 1);
poly falling(long long n, int k) {
  poly ans({1});
  mint p = n % mod;
  for (int i = 0; i < k; i++) {
    ans = ans * poly({p - i, 1});
  }
  return ans;
}
// number of solutions of the equation x_0 + ... + x_(n-1) = s s.t. 0 <= x_i <= a_i
// O(2^(n/2)*n^2)
mint yo(vector<long long> a, long long s) {
  int n = a.size();
  for (auto &x: a) ++x;
  vector<long long> l, r;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) l.push_back(a[i]);
    else r.push_back(a[i]);
  }
  auto L = get(l);
  auto R = get(r);
  sort(L.begin(), L.end());
  sort(R.rbegin(), R.rend());
  int i = 0;
  poly f({0});
  mint ans = 0;
  for (auto [x, y]: R) {
    while (i < L.size() and L[i].first + x <= s) {
      if (L[i].second == 1) f = f + falling(s + n - 1 - L[i].first, n - 1);
      else f = f - falling(s + n - 1 - L[i].first, n - 1);
      ++i;
    }
    ans += eval(f, (-x % mod + mod) % mod) * y;
  }
  for (int i = 1; i <= n - 1; i++) {
    ans /= i;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<long long> a(n);
    long long s = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      --a[i];
      s += a[i];
    }
    s /= 2;
    cout << yo(a, s) << '\n';
  }
  return 0;
}
// https://codeforces.com/gym/102114/problem/F

// Number of Nonnegative Integer Solutions to ax+by <= c:

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// number of integer solutions to ax + by <= c s.t. x, y >= 0
// number of nonnegative integer lattice points under or on the line ax + by = c
ll lattice_cnt(ll a, ll b, ll c) {
  assert(a >= 0 && b >= 0);
  if (c < 0) return 0;
  if (a == 0 or b == 0) {
    // infinite solutions
    assert(0);
    return -1;
  }
  assert(a > 0 && b > 0);
  if (a > b) swap(a, b);
  ll ans = 0;
  while (c >= 0) {
    ll k = b / a;
    ll l = b % a;
    ll f = c / b;
    ll e = c % b / a;
    ll g = c % b % a;
    ans += (f + 1) * (e + 1) + (f + 1) * f / 2 * k;
    c = f * l - a + g;
    b = a;
    a = l;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << lattice_cnt(2, 3, 5) << '\n';
  return 0;
}

// Number of Solutions to a Basic Linear Algebraic Equation with Variable Upper Bound Constraints:

#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

template <const int32_t MOD>
struct modint {
  int32_t value;
  modint() = default;
  modint(int32_t value_) : value(value_) {}
  inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
  inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
  inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
  inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
  inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
  inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
  modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
  modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
  inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
  inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<MOD> other) const { return value == other.value; }
  inline bool operator != (modint<MOD> other) const { return value != other.value; }
  inline bool operator < (modint<MOD> other) const { return value < other.value; }
  inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

using poly = vector<mint>;

mint eval(poly a, mint x) {
  mint ans = 0, p = 1;
  for (mint b : a) {
    ans += p * b;
    p *= x;
  }
  return ans;
}
poly operator + (poly a, poly b) {
  if (a.size() < b.size()) a.resize(b.size(), 0);
  for (int i = 0; i < b.size(); i++) {
    a[i] += b[i];
  }
  return a;
}
poly operator - (poly a, poly b) {
  if (a.size() < b.size()) a.resize(b.size(), 0);
  for (int i = 0; i < b.size(); i++) {
    a[i] -= b[i];
  }
  return a;
}
poly operator * (poly a, poly b) {
  vector<mint> r(a.size() + b.size() - 1, 0);
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      r[i + j] += a[i] * b[j];
    }
  }
  return r;
}
vector<pair<long long, int>> get(vector<long long> a) {
  int n = a.size();
  vector<pair<long long, int>> ans;
  for (int mask = 0; mask < (1 << n); mask++) {
    long long add = 0; int x = 1;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        add += a[i];
        x = -x;
      }
    }
    ans.push_back({add, x});
  }
  return ans;
}
// (x + n)(x + n - 1)...(x + n - k + 1);
poly falling(long long n, int k) {
  poly ans({1});
  mint p = n % mod;
  for (int i = 0; i < k; i++) {
    ans = ans * poly({p - i, 1});
  }
  return ans;
}
// returns the number of solutions to the equation x_0 + ... + x_(n-1) = s s.t. 0 <= x_i <= a_i
// O(2^(n/2)*n^2)
mint yo(vector<long long> a, long long s) {
  int n = a.size();
  for (auto &x: a) ++x;
  vector<long long> l, r;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) l.push_back(a[i]);
    else r.push_back(a[i]);
  }
  auto L = get(l);
  auto R = get(r);
  sort(L.begin(), L.end());
  sort(R.rbegin(), R.rend());
  int i = 0;
  poly f({0});
  mint ans = 0;
  for (auto [x, y]: R) {
    while (i < L.size() and L[i].first + x <= s) {
      if (L[i].second == 1) f = f + falling(s + n - 1 - L[i].first, n - 1);
      else f = f - falling(s + n - 1 - L[i].first, n - 1);
      ++i;
    }
    ans += eval(f, (-x % mod + mod) % mod) * y;
  }
  for (int i = 1; i <= n - 1; i++) {
    ans /= i;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<long long> a(n);
    long long s = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      --a[i];
      s += a[i];
    }
    s /= 2;
    cout << yo(a, s) << '\n';
  }
  return 0;
}
// https://codeforces.com/gym/102114/problem/F

// Number of Solutions to a Basic Linear Algebraic Equation:

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, mod = 1e9 + 7;

template <const int32_t MOD>
struct modint {
  int32_t value;
  modint() = default;
  modint(int32_t value_) : value(value_) {}
  inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
  inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
  inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
  inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
  inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
  inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
  modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
  modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
  inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
  inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<MOD> other) const { return value == other.value; }
  inline bool operator != (modint<MOD> other) const { return value != other.value; }
  inline bool operator < (modint<MOD> other) const { return value < other.value; }
  inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

struct Combi{
  int n; vector<mint> facts, finvs, invs;
  Combi(int _n): n(_n), facts(_n), finvs(_n), invs(_n){
    facts[0] = finvs[0] = 1;
    invs[1] = 1;
      for (int i = 2; i < n; i++) invs[i] =  invs[mod % i] * (-mod / i);
    for(int i = 1; i < n; i++){
      facts[i] = facts[i - 1] * i;
      finvs[i] = finvs[i - 1] * invs[i];
    }
  }
  inline mint fact(int n) { return facts[n]; }
  inline mint finv(int n) { return finvs[n]; }
  inline mint inv(int n) { return invs[n]; }
  inline mint ncr(int n, int k) { return n < k ? 0 : facts[n] * finvs[k] * finvs[n-k]; }
};
Combi C(N);

// returns the number of solutions to the equation
// x_1 + x_2 + ... + x_n = s and 0 <= l <= x_i <= r
mint yo(int n, int s, int l, int r) {
  if (s < l * n) return 0;
  s -= l * n;
  r -= l;
  mint ans = 0;
  for (int k = 0; k <= n; k++) {
    mint cur = C.ncr(s - k - k * r + n - 1 + 1, n - 1 + 1) * C.ncr(n, k);
    if (k & 1) ans -= cur;
    else ans += cur;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << yo(3, 3, 0, 1) << '\n';
  return 0;
}