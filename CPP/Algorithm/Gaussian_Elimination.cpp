// Gaussian Elimination:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

const double eps = 1e-9;
int Gauss(vector<vector<double>> a, vector<double> &ans)
{
    int n = (int)a.size(), m = (int)a[0].size() - 1;
    vector<int> pos(m, -1);
    double det = 1;
    int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int mx = row;
        for (int i = row; i < n; i++)
            if (fabs(a[i][col]) > fabs(a[mx][col]))
                mx = i;
        if (fabs(a[mx][col]) < eps)
        {
            det = 0;
            continue;
        }
        for (int i = col; i <= m; i++)
            swap(a[row][i], a[mx][i]);
        if (row != mx)
            det = -det;
        det *= a[row][col];
        pos[col] = row;
        for (int i = 0; i < n; i++)
        {
            if (i != row && fabs(a[i][col]) > eps)
            {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++)
                    a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
        ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++)
    {
        if (pos[i] != -1)
            ans[i] = a[pos[i]][m] / a[pos[i]][i];
    }
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int j = 0; j < m; j++)
            sum += ans[j] * a[i][j];
        if (fabs(sum - a[i][m]) > eps)
            return -1; // no solution
    }
    for (int i = 0; i < m; i++)
        if (pos[i] == -1)
            return 2; // infinte solutions
    return 1;         // unique solution
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<double>> v(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            double x;
            cin >> x;
            v[i].push_back(x);
        }
    }
    vector<double> ans;
    int k = Gauss(v, ans);
    if (k)
        for (int i = 0; i < n; i++)
            cout << fixed << setprecision(5) << ans[i] << ' ';
    else
        cout << "no solution\n";
    return 0;
}

// Gaussian Elimination Mudular:

#include <bits/stdc++.h>
using namespace std;

const int N = 105, mod = 1e9 + 7;

int power(long long n, long long k)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0)
        n += mod;
    while (k)
    {
        if (k & 1)
            ans = (long long)ans * n % mod;
        n = (long long)n * n % mod;
        k >>= 1;
    }
    return ans;
}
int Gauss(vector<vector<int>> a, vector<int> &ans)
{
    int n = a.size(), m = (int)a[0].size() - 1;
    vector<int> pos(m, -1);
    int free_var = 0;
    const long long MODSQ = (long long)mod * mod;
    int det = 1, rank = 0;
    for (int col = 0, row = 0; col < m && row < n; col++)
    {
        int mx = row;
        for (int k = row; k < n; k++)
            if (a[k][col] > a[mx][col])
                mx = k;
        if (a[mx][col] == 0)
        {
            det = 0;
            continue;
        }
        for (int j = col; j <= m; j++)
            swap(a[mx][j], a[row][j]);
        if (row != mx)
            det = det == 0 ? 0 : mod - det;
        det = 1LL * det * a[row][col] % mod;
        pos[col] = row;
        int inv = power(a[row][col], mod - 2);
        for (int i = 0; i < n && inv; i++)
        {
            if (i != row && a[i][col])
            {
                int x = ((long long)a[i][col] * inv) % mod;
                for (int j = col; j <= m && x; j++)
                {
                    if (a[row][j])
                        a[i][j] = (MODSQ + a[i][j] - ((long long)a[row][j] * x)) % mod;
                }
            }
        }
        row++;
        ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++)
    {
        if (pos[i] == -1)
            free_var++;
        else
            ans[i] = ((long long)a[pos[i]][m] * power(a[pos[i]][i], mod - 2)) % mod;
    }
    for (int i = 0; i < n; i++)
    {
        long long val = 0;
        for (int j = 0; j < m; j++)
            val = (val + ((long long)ans[j] * a[i][j])) % mod;
        if (val != a[i][m])
            return -1; // no solution
    }
    return free_var; // has solution
}

int32_t main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            cin >> a[i][j];
    vector<int> ans;
    int k = Gauss(a, ans);
    if (k == -1)
        cout << "no solution\n";
    else
    {
        for (auto x : ans)
            cout << x << '\n';
    }
    return 0;
}

// Gaussian Elimination Modulo 2:

#include <bits/stdc++.h>
using namespace std;

const int N = 2010;

// n = number of equations, m = number of variables
int Gauss(int n, int m, vector<bitset<N>> a, bitset<N> &ans)
{
    // reversing for lexocgraphically largest solution
    for (int i = 0; i < n; i++)
    {
        bitset<N> tmp;
        for (int j = 0; j < m; j++)
            tmp[j] = a[i][m - j - 1];
        tmp[m] = a[i][m];
        a[i] = tmp;
    }
    int rank = 0, det = 1;
    vector<int> pos(N, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int mx = row;
        for (int i = row; i < n; ++i)
            if (a[i][col])
            {
                mx = i;
                break;
            }
        if (!a[mx][col])
        {
            det = 0;
            continue;
        }
        swap(a[mx], a[row]);
        if (row != mx)
            det = det == 0 ? 0 : 1;
        det &= a[row][col];
        pos[col] = row;
        // forward elimination
        for (int i = row + 1; i < n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row, ++rank;
    }
    ans.reset();
    // backward substituition
    for (int i = m - 1; i >= 0; i--)
    {
        if (pos[i] == -1)
            ans[i] = true;
        else
        {
            int k = pos[i];
            for (int j = i + 1; j < m; j++)
                if (a[k][j])
                    ans[i] = ans[i] ^ ans[j];
            ans[i] = ans[i] ^ a[k][m];
        }
    }
    for (int i = rank; i < n; ++i)
        if (a[i][m])
            return -1; // no solution
    // reversing again beacuse we reversed earlier
    bitset<N> tmp;
    for (int j = 0; j < m; j++)
        tmp[j] = ans[m - j - 1];
    ans = tmp;
    int free_var = 0;
    for (int i = 0; i < m; ++i)
        if (pos[i] == -1)
            free_var++;
    return free_var; // has solution
}
string read()
{
    string t;
    if (!(cin >> t))
        return "";
    if (t.empty() || t == "and")
        return "";
    while (t[0] == '(')
        t.erase(t.begin());
    while (t.back() == ')')
        t.pop_back();
    return t;
}
bool is_var(string t) { return t.size() > 0 && t[0] == 'x'; }
int get_var(string t) { return atoi(t.substr(1).c_str()) - 1; }
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<bitset<N>> bs(n, bitset<N>(0));
    for (int i = 0; i < n; i++)
    {
        string s;
        bool eq = 1;
        while ((s = read()).size() > 0)
        {
            if (is_var(s))
            {
                int x = get_var(s);
                bs[i][x] = bs[i][x] ^ 1;
            }
            else if (s == "not")
                eq ^= 1;
        }
        bs[i][m] = eq;
    }
    bitset<N> ans;
    int ok = Gauss(n, m, bs, ans);
    if (ok == -1)
        cout << "impossible\n";
    else
    {
        for (int i = 0; i < m; i++)
            cout << "FT"[ans[i]];
        cout << '\n';
    }
    return 0;
}
// https://codeforces.com/gym/101908/problem/M