// Quadratic Equation: a*x^2 + b*x + c = 0;
// Complexity: O(log(D)), D = d

double a, b, c, x1, x2; string i1, i2;
void sol() {
    double d = b * b - 4.0 * a * c, dum = 2.0 * a;
    if (d > 0) {  // Roots are real and different
        double rt = sqrt(d);
        x1 = (-b + rt) / dum; x2 = (-b - rt) / dum;
    }
    else {
        x1 = x2 = -b / dum;  // Roots are real and same
        if (d < 0) {  // Roots are complex and different
            string img = to_string(sqrt(-d) / dum);
            i1 = '+' + img + 'i'; i2 = '-' + img + 'i';
        }
    }
}

// Operation:
    cin >> a >> b >> c;
    sol();
    cout << x1 << i1 << '\n';
    cout << x2 << i2 << '\n';


// Cubic Equation: a*x^3 + b*x^2 + c*x + d = 0;
// Complexity:

double a, b, c, d, x, x1, x2; string i1, i2;
void sol() {
    b /= a; c /= a; d /= a;
    double q = (3.0 * c - (b * b)) / 9.0;
    double r = (-(27.0 * d) + b * (9.0 * c - 2.0 * (b * b))) / 54.0;
    double disc = q * q * q + r * r, term1 = (b / 3.0);
    if (disc > 0) {  // One root is real, two are complex
        double rt = sqrt(disc);
        double s = r + rt; s = s < 0 ? -cbrt(-s) : cbrt(s);
        double t = r - rt; t = t < 0 ? -cbrt(-t) : cbrt(t);
        x = -term1 + s + t; term1 += (s + t) / 2.0;
        x2 = x1 = -term1; term1 = sqrt(3.0) * (-t + s) / 2.0;
        double x1_imag = term1, x2_imag = -term1;
        string img = to_string(x1_imag);
        i1 = '+' + img + 'i'; i2 = '-' + img + 'i';
    }
    else if (!disc) {  // All roots are real, at least two are equal.
        double r13 = r < 0 ? -cbrt(-r) : cbrt(r);
        x = -term1 + 2.0 * r13; x1 = x2 = -(r13 + term1);
    }
    else {  // All roots are real and unequal
        q = -q; double r13 = 2.0 * sqrt(q);
        double dum1 = acos(r / sqrt(q * q * q));
        x = -term1 + r13 * cos(dum1 / 3.0);
        x1 = -term1 + r13 * cos((dum1 + 2.0 * M_PI) / 3.0);
        x2 = -term1 + r13 * cos((dum1 + 4.0 * M_PI) / 3.0);
    }
}

// Operation:
    cin >> a >> b >> c >> d;
    sol();
    cout << x << '\n';
    cout << x1 << i1 << '\n';
    cout << x2 << i2 << '\n';

// Number of Solutions to x^2 = 1 mod m:

#include<bits/stdc++.h>
using namespace std;

using ll = long long;
namespace PollardRho {
  mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
  const int P = 1e6 + 9;
  ll seq[P];
  int primes[P], spf[P];
  inline ll add_mod(ll x, ll y, ll m) {
    return (x += y) < m ? x : x - m;
  }
  inline ll mul_mod(ll x, ll y, ll m) {
    ll res = __int128(x) * y % m;
    return res;
    // ll res = x * y - (ll)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
  }
  inline ll pow_mod(ll x, ll n, ll m) {
    ll res = 1 % m;
    for (; n; n >>= 1) {
      if (n & 1) res = mul_mod(res, x, m);
      x = mul_mod(x, x, m);
    }
    return res;
  }
  // O(it * (logn)^3), it = number of rounds performed
  inline bool miller_rabin(ll n) {
    if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
    if (n < P) return spf[n] == n;
    ll c, d, s = 0, r = n - 1;
    for (; !(r & 1); r >>= 1, s++) {}
    // each iteration is a round
    for (int i = 0; primes[i] < n && primes[i] < 32; i++) {
      c = pow_mod(primes[i], r, n);
      for (int j = 0; j < s; j++) {
        d = mul_mod(c, c, n);
        if (d == 1 && c != 1 && c != (n - 1)) return false;
        c = d;
      }
      if (c != 1) return false;
    }
    return true;
  }
  void init() {
    int cnt = 0;
    for (int i = 2; i < P; i++) {
      if (!spf[i]) primes[cnt++] = spf[i] = i;
      for (int j = 0, k; (k = i * primes[j]) < P; j++) {
        spf[k] = primes[j];
        if (spf[i] == spf[k]) break;
      }
    }
  }
  // returns O(n^(1/4))
  ll pollard_rho(ll n) {
    while (1) {
      ll x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
      ll *px = seq, *py = seq;
      while (1) {
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        if ((x = *px++) == y) break;
        v = u;
        u = mul_mod(u, abs(y - x), n);
        if (!u) return __gcd(v, n);
        if (++t == 32) {
          t = 0;
          if ((u = __gcd(u, n)) > 1 && u < n) return u;
        }
      }
      if (t && (u = __gcd(u, n)) > 1 && u < n) return u;
    }
  }
  vector<ll> factorize(ll n) {
    if (n == 1) return vector <ll>();
    if (miller_rabin(n)) return vector<ll> {n};
    vector <ll> v, w;
    while (n > 1 && n < P) {
      v.push_back(spf[n]);
      n /= spf[n];
    }
    if (n >= P) {
      ll x = pollard_rho(n);
      v = factorize(x);
      w = factorize(n / x);
      v.insert(v.end(), w.begin(), w.end());
    }
    return v;
  }
}
// number of solutions to x^2 = 1 mod p^k
int f(int p, int k) {
  if (p == 2) {
    if (k == 1) return 1;
    if (k == 2) return 2;
    return 4;
  }
  return 2;
}
// number of solutions to x^2 = 1 mod n (0 <= x < n)
// from CRT -> x^2 = 1 mod p_i^q_i where n = mul(p_i^q_i)
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  PollardRho::init();
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    auto p = PollardRho::factorize(n);
    map<int, int> mp;
    for (auto x: p) mp[x]++;
    ll ans = 1;
    for (auto [p, k]: mp) {
      ans *= f(p, k);
    }
    cout << ans << '\n';
  }
  return 0;
}
// https://toph.co/p/congruence-problem

// Number of ax%p in a Range:

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

// number of integer solutions to ax + by <= c s.t. x, y >= 0
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
// returns the number of 0 <= (a * x % m) <= c s.t. 0 <= x <= n
ll mod_count(ll a, ll m, ll c, ll n) {
  ++c; ++n;
  assert(m > 0);
  if (n == 0) return 0;
  a %= m; if (a < 0) a += m;
  ll extra_c = c / m; c %= m;
  if (c < 0) extra_c--, c += m;
  assert(0 <= c && c < m);
  ll ans = extra_c * n;
  ll extra_n = n / m; n %= m;
  if (n < 0) extra_n--, n += m;
  assert(0 <= n && n < m);
  if (extra_n) {
    ans += extra_n * (lattice_cnt(m, a + m, (a + m) * (m - 1)) - lattice_cnt(m, a + m, (a + m) * (m - 1) - c));
  }
  if (n) {
    ans += lattice_cnt(m, a + m, (a + m) * (n - 1)) - lattice_cnt(m, a + m, (a + m) * (n - 1) - c);
  }
  return ans;
}
// returns the count of nlo <= x <= nhi s.t. clo <= (a * x % m) <= chi
ll mod_count_range(ll a, ll m, ll clo, ll chi, ll nlo, ll nhi) {
  return mod_count(a, m, chi, nhi) - mod_count(a, m, chi, nlo - 1) - mod_count(a, m, clo - 1, nhi) + mod_count(a, m, clo - 1, nlo - 1);
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}