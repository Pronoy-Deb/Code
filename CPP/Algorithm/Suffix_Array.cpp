// Complexity: O(n * log(n))
// Use: Sorts the suffixes of a string in lexicographical order and stores the starting index of each suffix.

int suf[N], n;
string s;
void sa() {
    map<string, int> mp; string sub;
    for (int i = n - 1; i >= 0; --i) {
        sub = s[i] + sub; mp[sub] = i;
    }
    int i = -1; for (auto &[f, se] : mp) suf[++i] = se;
}

// OR,

const int N = 3e5 + 9;
const int LG = 18;

void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
    vector<int> l(val_range, 0), r(val_range, 0);
    for (int c : vec) {
        if (c + 1 < val_range) ++l[c + 1];
        ++r[c];
    }
    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(SA.begin(), SA.end(), -1);
    for (int i = lms_idx.size() - 1; i >= 0; --i)
        SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    for (int i : SA)
        if (i >= 1 && sl[i - 1]) {
            SA[l[vec[i - 1]]++] = i - 1;
        }
    fill(r.begin(), r.end(), 0);
    for (int c : vec)
        ++r[c];
    partial_sum(r.begin(), r.end(), r.begin());
    for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
        if (i >= 1 && !sl[i - 1]) {
            SA[--r[vec[i - 1]]] = i - 1;
        }
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
    const int n = vec.size();
    vector<int> SA(n), lms_idx;
    vector<bool> sl(n);
    sl[n - 1] = false;
    for (int i = n - 2; i >= 0; --i) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1])
            lms_idx.push_back(i + 1);
    }
    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(vec, val_range, SA, sl, lms_idx);
    vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
    for (int i = 0, k = 0; i < n; ++i)
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
            new_lms_idx[k++] = SA[i];
        }
    int cur = 0;
    SA[n - 1] = cur;
    for (size_t k = 1; k < new_lms_idx.size(); ++k) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) {
            SA[j] = ++cur;
            continue;
        }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) {
                flag = true;
                break;
            }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
                break;
            }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    for (size_t i = 0; i < lms_idx.size(); ++i)
        lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < (int)lms_idx.size()) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        for (size_t i = 0; i < lms_idx.size(); ++i) {
            new_lms_idx[i] = lms_idx[lms_SA[i]];
        }
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx);
    return SA;
}
vector<int> suffix_array(const string &s, const int LIM = 128) {
    vector<int> vec(s.size() + 1);
    copy(begin(s), end(s), begin(vec));
    vec.back() = '$';
    auto ret = SA_IS(vec, LIM);
    ret.erase(ret.begin());
    return ret;
}
struct SuffixArray {
    int n;
    string s;
    vector<int> sa, rank, lcp;
    vector<vector<int>> t;
    vector<int> lg;
    SuffixArray() {}
    SuffixArray(string _s) {
        n = _s.size();
        s = _s;
        sa = suffix_array(s);
        rank.resize(n);
        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;
        costruct_lcp();
        prec();
        build();
    }
    void costruct_lcp() {
        int k = 0;
        lcp.resize(n - 1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
        }
    }
    void prec() {
        lg.resize(n, 0);
        for (int i = 2; i < n; i++)
            lg[i] = lg[i / 2] + 1;
    }
    void build() {
        int sz = n - 1;
        t.resize(sz);
        for (int i = 0; i < sz; i++) {
            t[i].resize(LG);
            t[i][0] = lcp[i];
        }
        for (int k = 1; k < LG; ++k) {
            for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
                t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    int query(int l, int r) {  // minimum of lcp[l], ..., lcp[r]
        int k = lg[r - l + 1];
        return min(t[l][k], t[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) {  // lcp of suffix starting from i and j
        if (i == j)
            return n - i;
        int l = rank[i], r = rank[j];
        if (l > r)
            swap(l, r);
        return query(l, r - 1);
    }
    int lower_bound(string &t) {
        int l = 0, r = n - 1, k = t.size(), ans = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (s.substr(sa[mid], min(n - sa[mid], k)) >= t)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        return ans;
    }
    int upper_bound(string &t) {
        int l = 0, r = n - 1, k = t.size(), ans = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (s.substr(sa[mid], min(n - sa[mid], k)) > t)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        return ans;
    }
    // occurrences of s[p, ..., p + len - 1]
    pair<int, int> find_occurrence(int p, int len) {
        p = rank[p];
        pair<int, int> ans = {p, p};
        int l = 0, r = p - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(mid, p - 1) >= len)
                ans.first = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        l = p + 1, r = n - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(p, mid - 1) >= len)
                ans.second = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        return ans;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    SuffixArray sa(s);
    for (int i = 0; i < s.size(); i++)
        cout << sa.sa[i] << '\n';
    return 0;
}

// Suffix Array Isomorphic:

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

const int kinds = N;
int str[N];
int buc[N], r[N], suf[N], X[N], Y[N], high[N];
bool cmp(int *r, int a, int b, int x) {
    return (r[a] == r[b] && r[a + x] == r[b + x]);
}
void suffix_array_DA(int n, int m) {
    int *x = X, *y = Y, i, j, k = 0, l;
    for (i = 0; i <= max(n, m); i++)
        buc[i] = 0;
    for (i = 0; i < n; i++)
        buc[x[i] = str[i]]++;
    for (i = 1; i < m; i++)
        buc[i] += buc[i - 1];
    for (i = n - 1; i >= 0; i--)
        suf[--buc[x[i]]] = i;
    for (l = 1, j = 1; j < n; m = j, l <<= 1) {
        j = 0;
        for (i = n - l; i < n; i++)
            y[j++] = i;
        for (i = 0; i < n; i++)
            if (suf[i] >= l)
                y[j++] = suf[i] - l;
        for (i = 0; i < m; i++)
            buc[i] = 0;
        for (i = 0; i < n; i++)
            buc[x[y[i]]]++;
        for (i = 1; i < m; i++)
            buc[i] += buc[i - 1];
        for (i = n - 1; i >= 0; i--)
            suf[--buc[x[y[i]]]] = y[i];
        for (swap(x, y), x[suf[0]] = 0, i = 1, j = 1; i < n; i++) {
            x[suf[i]] = cmp(y, suf[i - 1], suf[i], l) ? j - 1 : j++;
        }
    }
    for (i = 1; i < n; i++)
        r[suf[i]] = i;
    for (i = 0; i < n - 1; high[r[i++]] = k) {
        for (k ? k-- : 0, j = suf[r[i] - 1]; str[i + k] == str[j + k]; k++);
    }
}
struct SuffixArray {
    int n;
    vector<int> s;
    vector<int> sa, rank, lcp;
    static const int LG = 18;
    vector<vector<int>> t;
    vector<int> lg;
    SuffixArray() {}
    SuffixArray(vector<int> _s) {
        n = _s.size();
        s = _s;
        for (int i = 0; i < n; i++)
            str[i] = s[i];  // for integers, each element should be positive
        str[n] = 0;
        suffix_array_DA(n + 1, kinds);
        for (int i = 1; i <= n; i++)
            sa.push_back(suf[i]);
        rank.resize(n);
        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;
        costruct_lcp();
        prec();
        build();
    }
    void costruct_lcp() {
        int k = 0;
        lcp.resize(n - 1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
        }
    }
    void prec() {
        lg.resize(n, 0);
        for (int i = 2; i < n; i++)
            lg[i] = lg[i / 2] + 1;
    }
    void build() {
        int sz = n - 1;
        t.resize(sz);
        for (int i = 0; i < sz; i++) {
            t[i].resize(LG);
            t[i][0] = lcp[i];
        }
        for (int k = 1; k < LG; ++k) {
            for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
                t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    int query(int l, int r) {  // minimum of lcp[l], ..., lcp[r]
        int k = lg[r - l + 1];
        return min(t[l][k], t[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) {  // lcp of suffix starting from i and j
        if (i == j)
            return n - i;
        int l = rank[i], r = rank[j];
        if (l > r)
            swap(l, r);
        return query(l, r - 1);
    }
};
struct IsomorphicSuffixArray {
    string s;
    int n;
    vector<int> sa, rank, lcp, a;
    static const int LG = 18;
    vector<vector<int>> t;
    vector<int> lg;
    SuffixArray S;
    IsomorphicSuffixArray() {}
    IsomorphicSuffixArray(string _s) {
        s = _s;
        n = s.size();
        vector<int> last(26, -1);
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = last[s[i] - 'a'] == -1 ? 1 : i - last[s[i] - 'a'] + 1;
            last[s[i] - 'a'] = i;
        }
        S = SuffixArray(a);
        sa.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(),
             [&](const int &i, const int &j) {  // O(alpha)
                 for (int l = 0; l < n;) {
                     int x = i + l, y = j + l;
                     if (x >= n)
                         return true;
                     if (y >= n)
                         return false;
                     int vx = a[x] > l + 1 ? 1 : a[x];
                     int vy = a[y] > l + 1 ? 1 : a[y];
                     if (vx != vy)
                         return vx < vy;
                     l += max(1, S.get_lcp(x, y));
                 }
                 return false;
             });
        rank.resize(n);
        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;
        costruct_lcp();
        prec();
        build();
    }
    int get_lcp_brute(const int &i, const int &j) {  // O(alpha)
        for (int l = 0; l < n;) {
            int x = i + l, y = j + l;
            if (x >= n || y >= n)
                return l;
            int vx = a[x] > l + 1 ? 1 : a[x];
            int vy = a[y] > l + 1 ? 1 : a[y];
            if (vx != vy)
                return l;
            l += max(1, S.get_lcp(x, y));
        }
        return n;
    }
    void costruct_lcp() {
        lcp.resize(n - 1, 0);
        for (int i = 0; i < n - 1; i++) {
            lcp[i] = get_lcp_brute(sa[i], sa[i + 1]);
        }
    }
    void prec() {
        lg.resize(n, 0);
        for (int i = 2; i < n; i++)
            lg[i] = lg[i / 2] + 1;
    }
    void build() {
        int sz = n - 1;
        t.resize(sz);
        for (int i = 0; i < sz; i++) {
            t[i].resize(LG);
            t[i][0] = lcp[i];
        }
        for (int k = 1; k < LG; ++k) {
            for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
                t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    int query(int l, int r) {  // minimum of lcp[l], ..., lcp[r]
        int k = lg[r - l + 1];
        return min(t[l][k], t[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) {  // lcp of suffix starting from i and j
        if (i == j)
            return n - i;
        int l = rank[i], r = rank[j];
        if (l > r)
            swap(l, r);
        return query(l, r - 1);
    }
    // occurrences of s[p, ..., p + len - 1]
    pair<int, int> find_occurrence(int p, int len) {
        p = rank[p];
        pair<int, int> ans = {p, p};
        int l = 0, r = p - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(mid, p - 1) >= len)
                ans.first = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        l = p + 1, r = n - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(p, mid - 1) >= len)
                ans.second = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        return ans;
    }
};
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    IsomorphicSuffixArray sa(s);
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        auto ans = sa.find_occurrence(l, r - l + 1);
        cout << ans.second - ans.first + 1 << '\n';
    }
    return 0;
}
// https://www.hackerrank.com/challenges/similar-strings/problem