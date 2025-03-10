// Intgration (Romberg):

#include <bits/stdc++.h>
using namespace std;

#define double long double
const double eps = 1e-6;

int z, d;
double f(double x) {
    double t1 = sqrt(x * x + z * z);
    double t2 = sqrt((x + d) * (x + d) + z * z);
    double w = (t2 - t1) + (d - (t2 - t1)) / 2.0;
    double ans = w * w * 0.5 + t1 * w;
    ans += (d - w) * (d - w) * 0.5 + t2 * (d - w);
    ans /= d; return ans;
}
double integrate(double l, double r) {
    vector<double> t; double h = r - l;
    double last, curr; int k = 1, i = 1;
    t.push_back(h * (f(l) + f(r)) / 2);
    while (true) {
        last = t.back();
        curr = 0;
        double x = l + h / 2;
        for (int j = 0; j < k; j++)
            curr += f(x), x += h;
        curr = (t[0] + h * curr) / 2;
        double k1 = 4.0 / 3.0, k2 = 1.0 / 3.0;
        for (int j = 0; j < i; j++) {
            double temp = k1 * curr - k2 * t[j];
            t[j] = curr;
            curr = temp;
            k2 /= 4 * k1 - k2;
            k1 = k2 + 1;
        }
        t.push_back(curr);
        k *= 2; h /= 2;
        i++;
        if (fabs(last - curr) < eps) break;
    }
    return t.back();
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, cs = 0;
    cin >> t;
    while (t--) {
        int r, l;
        cin >> z >> r >> l >> d;
        r -= d;
        double ans;
        if (l == r) ans = f(l);
        else ans = integrate(l, r) / (r - l);
        cout << "Case " << ++cs << ": " << fixed << setprecision(10) << ans << '\n';
    }
    return 0;
}
// https://vjudge.net/problem/UVA-12997

// Integration (Simpsons):

#include <bits/stdc++.h>
using namespace std;

#define double long double
const double eps = 1e-6;

int z, d;
double f(double x)
{
    double t1 = sqrt(x * x + z * z);
    double t2 = sqrt((x + d) * (x + d) + z * z);
    double w = (t2 - t1) + (d - (t2 - t1)) / 2.0;
    double ans = w * w * 0.5 + t1 * w;
    ans += (d - w) * (d - w) * 0.5 + t2 * (d - w);
    ans /= d;
    return ans;
}
inline double simpson(double fl, double fr, double fmid, double l, double r)
{
    return (fl + fr + 4.0 * fmid) * (r - l) / 6.0;
}
double solve(double slr, double fl, double fr, double fmid, double l, double r)
{
    double mid = (l + r) / 2;
    double fml = f((l + mid) / 2);
    double fmr = f((mid + r) / 2);
    double slm = simpson(fl, fmid, fml, l, mid);
    double smr = simpson(fmid, fr, fmr, mid, r);
    if (fabs(slr - slm - smr) < eps)
        return slm + smr;
    return solve(slm, fl, fmid, fml, l, mid) + solve(smr, fmid, fr, fmr, mid, r);
}
// integrate in range [l, r]
double integrate(double l, double r)
{
    double mid = (l + r) / 2, fl = f(l), fr = f(r), fmid = f(mid);
    double slr = simpson(fl, fr, fmid, l, r);
    return solve(slr, fl, fr, fmid, l, r);
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, cs = 0;
    cin >> t;
    while (t--)
    {
        int r, l;
        cin >> z >> r >> l >> d;
        r -= d;
        double ans;
        if (l == r)
            ans = f(l);
        else
            ans = integrate(l, r) / (r - l);
        cout << "Case " << ++cs << ": " << fixed << setprecision(10) << ans << '\n';
    }
    return 0;
}
// https://vjudge.net/problem/UVA-12997