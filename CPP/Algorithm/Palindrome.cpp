// Is Palindrome?: O(|s|)

bool pal(string &s) {
    for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

// Hashing Approach:

bool pal(string &s, int b = 29) {
    long long sz = s.size(), l = s[0] - 'a', r = s[sz - 1] - 'a';
    for (int i = 1; i < sz; ++i) l = ((l * b) + (s[i] - 'a')) % M;
    for (int i = sz - 2; i >= 0; --i) r = ((r * b) + (s[i] - 'a')) % M;
    return (l == r);
}

// Longest Palindrome: O(n)
// Note: Inspired from Manacher algorithm
https://cses.fi/problemset/task/1111

auto man(string &s) {
    string t = "$#";
    for (auto &c : s) t += c + string("#"); t += '^';
    int n = t.size(), l = 0, r = 0, len = 0, in = -1, p[n];
    for (int i = 0; i < n; ++i) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (t[i - p[i]] == t[i + p[i]]) ++p[i];
        if (i + p[i] > r) { l = i - p[i]; r = i + p[i]; }
        if (p[i] > len) { len = p[i]; in = i; }
    }
    return {len - 1, (in >> 1) - 1};
}

// Operation:
    string s; cin >> s;
    auto pr = man(s);
    int i = pr.second - (pr.first >> 1) + (~pr.first & 1), j = 0;
    while (++j <= pr.first) cout << s[i++];

// Number of Palindromic Subsequence having length k: O(n^2 * k)

int n;
long long psk(string &s, int K) {
	long long dp[n + 2][n + 2][K + 1]{};
    for (int i = n; i >= 1; --i) {
        for (int j = i; j <= n; ++j) {
            dp[i][j][0] = 1; dp[i][j][1] = j - i + 1;
            if (i + 1 == j) {
                if (s[i - 1] == s[j - 1]) dp[i][j][2] = 1; continue;
            }
            for (int k = 3; k <= K; ++k)
                dp[i][j][k] = (s[i - 1] == s[j - 1]) * dp[i + 1][j - 1][k - 2] + dp[i][j - 1][k] + dp[i + 1][j][k] - dp[i + 1][j - 1][k];
        }
    }
    return dp[1][n][K];
}


// If k <= 3: O(26 * n)

long long l[26][N], r[26][N], n;
void pre(string &s) {
	l[s[0] - 'a'][0] = 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 26; ++j) l[j][i] += l[j][i - 1];
		++l[s[i] - 'a'][i];
	}
	r[s[n - 1] - 'a'][n - 1] = 1;
	for (int i = n - 2; i >= 0; --i) {
		for (int j = 0; j < 26; ++j) r[j][i] += r[j][i + 1];
		++r[s[i] - 'a'][i];
	}
}
long long psk(int k) {
	long long ans = 0;
	if (k == 1) {
		for (int i = 0; i < 26; ++i) ans += l[i][n - 1];
		return ans;
	}
	if (k == 2) {
		for (int i = 0; i < 26; ++i) ans += ((l[i][n - 1] * (l[i][n - 1] - 1)) >> 1);
		return ans;
	}
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 0; j < 26; ++j) ans += l[j][i - 1] * r[j][i + 1];
	}
	return ans;
}

// Minimum Palindrome Factorization:

/*
-> diff(v) = len(v) - len(link(v))
-> series link will lead from the vertex v to the vertex u corresponding
   to the maximum suffix palindrome of v which satisfies diff(v) != diff(u)
-> path within series links to the root contains only O(log n) vertices
-> cnt contains the number of palindromic suffixes of the node
*/
struct PalindromicTree {
    struct node {
        int nxt[26], len, st, en, link, diff, slink, cnt, oc;
    };
    string s;
    vector<node> t;
    int sz, last;
    PalindromicTree() {}
    PalindromicTree(string _s) {
        s = _s;
        int n = s.size();
        t.clear();
        t.resize(n + 9);
        sz = 2, last = 2;
        t[1].len = -1, t[1].link = 1;
        t[2].len = 0, t[2].link = 1;
        t[1].diff = t[2].diff = 0;
        t[1].slink = 1;
        t[2].slink = 2;
    }
    int extend(int pos) { // returns 1 if it creates a new palindrome
        int cur = last, curlen = 0;
        int ch = s[pos] - 'a';
        while (1) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;
            cur = t[cur].link;
        }
        if (t[cur].nxt[ch]) {
            last = t[cur].nxt[ch];
            t[last].oc++;
            return 0;
        }
        sz++;
        last = sz;
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;
        if (t[sz].len == 1) {
            t[sz].link = 2;
            t[sz].cnt = 1;
            t[sz].diff = 1;
            t[sz].slink = 2;
            return 1;
        }
        while (1) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            {
                t[sz].link = t[cur].nxt[ch];
                break;
            }
        }
        t[sz].cnt = 1 + t[t[sz].link].cnt;
        t[sz].diff = t[sz].len - t[t[sz].link].len;
        if (t[sz].diff == t[t[sz].link].diff)
            t[sz].slink = t[t[sz].link].slink;
        else
            t[sz].slink = t[sz].link;
        return 1;
    }
    void calc_occurrences() {
        for (int i = sz; i >= 3; i--)
            t[t[i].link].oc += t[i].oc;
    }
    vector<array<int, 2>> minimum_partition() { //(even, odd), 1 indexed
        int n = s.size();
        vector<array<int, 2>> ans(n + 1, {0, 0}), series_ans(n + 5, {0, 0});
        ans[0][1] = series_ans[2][1] = 1e9;
        for (int i = 1; i <= n; i++) {
            extend(i - 1);
            for (int k = 0; k < 2; k++)
            {
                ans[i][k] = 1e9;
                for (int v = last; t[v].len > 0; v = t[v].slink)
                {
                    series_ans[v][!k] = ans[i - (t[t[v].slink].len + t[v].diff)][!k];
                    if (t[v].diff == t[t[v].link].diff)
                        series_ans[v][!k] = min(series_ans[v][!k], series_ans[t[v].link][!k]);
                    ans[i][k] = min(ans[i][k], series_ans[v][!k] + 1);
                }
            }
        }
        return ans;
    }
} t;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    PalindromicTree t(s);
    for (int i = 0; i < s.size(); i++)
        t.extend(i);
    t.calc_occurrences();
    long long ans = 0;
    for (int i = 3; i <= t.sz; i++)
        ans += t.t[i].oc;
    cout << ans << '\n';
    return 0;
    // auto ans = t.minimum_partition();
    //  for (int i = 1; i <= s.size(); i++) {
    //      cout << (ans[i][1] == 1e9 ? -1 : ans[i][1]) << ' ';
    //      cout << (ans[i][0] == 1e9 ? -2 : ans[i][0]) << '\n';
    //  }
    return 0;
}
// https://acm.timus.ru/problem.aspx?space=1&num=2058

// Number of Palindromes in Range:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
vector<int> d1, d2;
void manachers(string &s) {
    int n = s.size();
    d1 = vector<int>(n); // maximum odd length palindrome centered at i
    // here d1[i]=the palindrome has d1[i]-1 right characters from i
    // e.g. for aba, d1[1]=2;
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    d2 = vector<int>(n); // maximum even length palindrome centered at i
    // here d2[i]=the palindrome has d2[i]-1 right characters from i
    // e.g. for abba, d2[2]=2;
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}
const int MAXN = (int)5100;
const int MAXV = (int)5100; // maximum value of any element in array

// array values can be negative too, use appropriate minimum and maximum value
struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    int *b, *c, bsz, csz; //  c holds the prefix sum of elements

    wavelet_tree() {
        lo = 1;
        hi = 0;
        bsz = 0;
        csz = 0, l = NULL;
        r = NULL;
    }

    void init(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (from >= to)
            return;
        int mid = (lo + hi) >> 1;
        auto f = [mid](int x) {
            return x <= mid;
        };
        b = (int *)malloc((to - from + 2) * sizeof(int));
        bsz = 0;
        b[bsz++] = 0;
        c = (int *)malloc((to - from + 2) * sizeof(int));
        csz = 0;
        c[csz++] = 0;
        for (auto it = from; it != to; it++) {
            b[bsz] = (b[bsz - 1] + f(*it));
            c[csz] = (c[csz - 1] + (*it));
            bsz++;
            csz++;
        }
        if (hi == lo)
            return;
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree();
        l->init(from, pivot, lo, mid);
        r = new wavelet_tree();
        r->init(pivot, to, mid + 1, hi);
    }
    // kth smallest element in [l, r]
    // for array [1,2,1,3,5] 2nd smallest is 1 and 3rd smallest is 2
    int kth(int l, int r, int k) {
        if (l > r)
            return 0;
        if (lo == hi)
            return lo;
        int inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
        if (k <= inLeft)
            return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }
    // count of numbers in [l, r] Less than or equal to k
    int LTE(int l, int r, int k) {
        if (l > r || k < lo)
            return 0;
        if (hi <= k)
            return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }
    // count of numbers in [l, r] equal to k
    int count(int l, int r, int k) {
        if (l > r || k < lo || k > hi)
            return 0;
        if (lo == hi)
            return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        int mid = (lo + hi) >> 1;
        if (k <= mid)
            return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    // sum of numbers in [l ,r] less than or equal to k
    int sum(int l, int r, int k) {
        if (l > r or k < lo)
            return 0;
        if (hi <= k)
            return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};
int get(int l, int r) {
    return r * (r + 1) / 2 - (l - 1) * l / 2;
}
wavelet_tree oddl, oddr;
int odd(int l, int r) {
    int m = (l + r) / 2;
    int c = 1 - l;
    int less_ = oddl.LTE(l, m, c);
    int ansl = get(l, m) + oddl.sum(l, m, c) + (m - l + 1 - less_) * c;
    c = 1 + r;
    less_ = oddr.LTE(m + 1, r, c);
    int ansr = -get(m + 1, r) + oddr.sum(m + 1, r, c) + (r - m - less_) * c;
    return ansl + ansr;
}
wavelet_tree evenl, evenr;
int even(int l, int r) {
    int m = (l + r) / 2;
    int c = -l;
    int less_ = evenl.LTE(l, m, c);
    int ansl = get(l, m) + evenl.sum(l, m, c) + (m - l + 1 - less_) * c;
    c = 1 + r;
    less_ = evenr.LTE(m + 1, r, c);
    int ansr = -get(m + 1, r) + evenr.sum(m + 1, r, c) + (r - m - less_) * c;
    return ansl + ansr;
}
int a[N], b[N], c[N], d[N];
int sc() {
    int c = getchar();
    int x = 0;
    int neg = 0;
    for (; ((c < 48 || c > 57) && c != '-'); c = getchar())
        ;
    if (c == '-') {
        neg = 1;
        c = getchar();
    }
    for (; c > 47 && c < 58; c = getchar()) {
        x = (x << 1) + (x << 3) + c - 48;
    }
    if (neg)
        x = -x;
    return x;
}
inline void out(int n) {
    int N = n < 0 ? -n : n, rev, cnt = 0;
    rev = N;
    if (N == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    while ((rev % 10) == 0) {
        cnt++;
        rev /= 10;
    }
    if (n < 0)
        putchar('-');
    rev = 0;
    while (N != 0) {
        rev = (rev << 3) + (rev << 1) + N % 10;
        N /= 10;
    }
    while (rev != 0) {
        putchar(rev % 10 + '0');
        rev /= 10;
    }
    while (cnt--)
        putchar('0');
    putchar('\n');
    return;
}
int main() {
    int i, j, k, n, m, q, l, r;
    string s;
    cin >> s;
    n = s.size();
    manachers(s);
    for (i = 1; i <= n; i++)
        a[i] = d1[i - 1] - i;
    oddl.init(a + 1, a + n + 1, -MAXV, MAXV);
    for (i = 1; i <= n; i++)
        b[i] = d1[i - 1] + i;
    oddr.init(b + 1, b + n + 1, -MAXV, MAXV);
    for (i = 1; i <= n; i++)
        c[i] = d2[i - 1] - i;
    evenl.init(c + 1, c + n + 1, -MAXV, MAXV);
    for (i = 1; i <= n; i++)
        d[i] = d2[i - 1] + i;
    evenr.init(d + 1, d + n + 1, -MAXV, MAXV);

    q = sc();
    for (i = 0; i < q; i++) {
        l = sc();
        r = sc();
        out(odd(l, r) + even(l, r));
    }
    return 0;
}
// https://codeforces.com/contest/245/problem/H

// Palindromic Tree:

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

/*
-> cnt contains the number of palindromic suffixes of the node
*/
struct PalindromicTree {
    struct node {
        int nxt[26], len, st, en, link, cnt, oc;
    };
    string s;
    vector<node> t;
    int sz, last;
    PalindromicTree() {}
    PalindromicTree(string _s) {
        s = _s;
        int n = s.size();
        t.clear();
        t.resize(n + 9);
        sz = 2, last = 2;
        t[1].len = -1, t[1].link = 1;
        t[2].len = 0, t[2].link = 1;
    }
    int extend(int pos) { // returns 1 if it creates a new palindrome
        int cur = last, curlen = 0;
        int ch = s[pos] - 'a';
        while (1) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;
            cur = t[cur].link;
        }
        if (t[cur].nxt[ch]) {
            last = t[cur].nxt[ch];
            t[last].oc++;
            return 0;
        }
        sz++;
        last = sz;
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;
        if (t[sz].len == 1) {
            t[sz].link = 2;
            t[sz].cnt = 1;
            return 1;
        }
        while (1) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            {
                t[sz].link = t[cur].nxt[ch];
                break;
            }
        }
        t[sz].cnt = 1 + t[t[sz].link].cnt;
        return 1;
    }
    void calc_occurrences() {
        for (int i = sz; i >= 3; i--)
            t[t[i].link].oc += t[i].oc;
    }
} t;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    PalindromicTree t(s);
    for (int i = 0; i < s.size(); i++)
        t.extend(i);
    t.calc_occurrences();
    long long ans = 0; // number of palindromes
    for (int i = 3; i <= t.sz; i++)
        ans += t.t[i].oc;
    cout << ans << '\n';
    return 0;
}

// Palindromic Tree Persistent:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 9;

// cnt contains the number of palindromic suffixes of the node
// t[cur].smart_link[c] -> link to the maximum length of a palindromic suffix of t[cur]
// s.t. ch is the immediate previous char of that suffix
struct PalindromicTree {
    static const int A = 2;
    struct node {
        int nxt[A], len, st, en, link, cnt, oc, smart_link[A];
        node() {
            memset(nxt, 0, sizeof nxt);
            for (int i = 0; i < A; i++)
            {
                smart_link[i] = 1;
            }
        }
    };
    string s;
    vector<node> t;
    vector<array<int, 4>> changes;
    int sz, last;
    vector<int> pref;
    PalindromicTree() {
        s = "";
        t.resize(3);
        sz = 2, last = 2;
        t[1].len = -1, t[1].link = 1;
        t[2].len = 0, t[2].link = 1;
        changes.clear();
    }
    int extend(char c) {
        int cur = last, curlen = 0, pos = s.size();
        pref.push_back(0);
        if (pos) {
            pref[pos] = pref[pos - 1];
        }
        s += c;
        int ch = c - 'a';
        if (pos - t[cur].len - 1 < 0 || s[pos - t[cur].len - 1] != c) {
            cur = t[cur].smart_link[ch];
        }
        if (t[cur].nxt[ch]) {
            changes.push_back({last, t[cur].nxt[ch], -1, -1});
            last = t[cur].nxt[ch];
            t[last].oc++;
            return 0;
        }
        changes.push_back({last, -1, cur, ch});
        sz++;
        last = sz;
        t.emplace_back();
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        pref[pos] = max(pref[pos], t[sz].len);
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;
        if (t[sz].len == 1) {
            t[sz].link = 2;
            t[sz].cnt = 1;
            t[sz].smart_link[ch] = 2;
            return 1;
        }
        else {
            t[sz].link = t[t[cur].smart_link[ch]].nxt[ch];
            for (int i = 0; i < A; i++)
            {
                int x = t[sz].link;
                if (pos - t[x].len >= 0 && s[pos - t[x].len] - 'a' == i)
                {
                    t[sz].smart_link[i] = x;
                }
                else
                {
                    t[sz].smart_link[i] = t[x].smart_link[i];
                }
            }
        }
        t[sz].cnt = 1 + t[t[sz].link].cnt;
        return 1;
    }
    void rollback() {
        if (s.size() == 0)
            return;
        s.pop_back();
        pref.pop_back();
        auto x = changes.back();
        int prvlast = x[0], oc = x[1], c = x[2], ch = x[3];
        changes.pop_back();
        last = prvlast;
        if (oc == -1) {
            t[c].nxt[ch] = 0;
            t.pop_back();
            sz--;
        }
        else {
            t[oc].oc--;
        }
    }
} t;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> q;
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int k;
            cin >> k;
            t.extend(char(k + 'a'));
        }
        else {
            t.rollback();
        }
        cout << (t.s.empty() ? 0 : t.pref[t.s.size() - 1]) << '\n';
    }
    return 0;
}
// https://www.codechef.com/problems/BINPALIN