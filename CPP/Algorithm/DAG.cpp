// Number of DAG:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 998244353;

template <int32_t MOD>
struct modint
{
    int32_t value;
    modint() = default;
    modint(int32_t value_) : value(value_) {}
    inline modint<MOD> operator+(modint<MOD> other) const
    {
        int32_t c = this->value + other.value;
        return modint<MOD>(c >= MOD ? c - MOD : c);
    }
    inline modint<MOD> operator-(modint<MOD> other) const
    {
        int32_t c = this->value - other.value;
        return modint<MOD>(c < 0 ? c + MOD : c);
    }
    inline modint<MOD> operator*(modint<MOD> other) const
    {
        int32_t c = (int64_t)this->value * other.value % MOD;
        return modint<MOD>(c < 0 ? c + MOD : c);
    }
    inline modint<MOD> &operator+=(modint<MOD> other)
    {
        this->value += other.value;
        if (this->value >= MOD)
            this->value -= MOD;
        return *this;
    }
    inline modint<MOD> &operator-=(modint<MOD> other)
    {
        this->value -= other.value;
        if (this->value < 0)
            this->value += MOD;
        return *this;
    }
    inline modint<MOD> &operator*=(modint<MOD> other)
    {
        this->value = (int64_t)this->value * other.value % MOD;
        if (this->value < 0)
            this->value += MOD;
        return *this;
    }
    inline modint<MOD> operator-() const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const
    {
        modint<MOD> x = *this, y = 1;
        for (; k; k >>= 1)
        {
            if (k & 1)
                y *= x;
            x *= x;
        }
        return y;
    }
    modint<MOD> inv() const { return pow(MOD - 2); } // MOD must be a prime
    inline modint<MOD> operator/(modint<MOD> other) const { return *this * other.inv(); }
    inline modint<MOD> operator/=(modint<MOD> other) { return *this *= other.inv(); }
    inline bool operator==(modint<MOD> other) const { return value == other.value; }
    inline bool operator!=(modint<MOD> other) const { return value != other.value; }
};
template <int32_t MOD>
modint<MOD> operator*(int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD>
modint<MOD> operator*(int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD>
ostream &operator<<(ostream &out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

mint dp[1 << 18]; // dp[i] = number of DAG containing vertices of mask i
int e[1 << 18];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        e[1 << u] |= 1 << v;
        e[1 << v] |= 1 << u;
    }
    dp[0] = 1;
    for (int mask = 1; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1)
                e[mask] |= e[1 << i];
        for (int sub = mask; sub; sub = (sub - 1) & mask)
        {
            if (e[sub] & sub)
                continue;
            if (__builtin_popcount(sub) & 1)
                dp[mask] += dp[mask ^ sub];
            else
                dp[mask] -= dp[mask ^ sub];
        }
    }
    cout << dp[(1 << n) - 1] * m / 2 << '\n';
    return 0;
}
// https://codeforces.com/contest/1193/problem/A

// DAG Rechablity Dynamic:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

/*add_edge(s, t): insert edge (s,t) to the network if it does not make a cycle
is_reachable(s, t): return true iff there is a path s --> t
Algorithm by G.F. ITALIANO
Complexity: amortized O(n) per update*/
// 0-indexed
struct Italiano
{
    int n;
    vector<vector<int>> par;
    vector<vector<vector<int>>> child;
    Italiano(int n) : n(n), par(n, vector<int>(n, -1)), child(n, vector<vector<int>>(n)) {}
    bool is_reachable(int s, int t)
    {
        return s == t || par[s][t] >= 0;
    }
    bool add_edge(int s, int t)
    {
        if (is_reachable(t, s))
            return 0; // break DAG condition
        if (is_reachable(s, t))
            return 1; // no-modification performed
        for (int p = 0; p < n; ++p)
        {
            if (is_reachable(p, s) && !is_reachable(p, t))
                meld(p, t, s, t);
        }
        return 1;
    }
    void meld(int root, int sub, int u, int v)
    {
        par[root][v] = u;
        child[root][u].push_back(v);
        for (int c : child[sub][v])
        {
            if (!is_reachable(root, c))
                meld(root, sub, v, c);
        }
    }
};
// add edges one by one. if it breaks DAG law then print it
int32_t main()
{
    int n, m;
    cin >> n >> m;
    Italiano t(n);
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        if (t.is_reachable(v, u))
            cout << u + 1 << ' ' << v + 1 << '\n';
        else
            t.add_edge(u, v);
    }
    cout << 0 << ' ' << 0 << '\n';
    return 0;
}
// https://www.spoj.com/problems/GHOSTS/