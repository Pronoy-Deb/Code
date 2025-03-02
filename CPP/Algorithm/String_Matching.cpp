// KMP(Knuth Morris Pratt): O(|p| + |s|)
// Application: Used to find all occurrences of a pattern in a text in linear time
lightoj.com/problem/substring-frequency

auto kmp(auto &str, auto &pat) {
    int pl = pat.size(), sl = str.size(), sz = max(pl, sl) + 5, pi[sz], now = pi[0] = -1;
    for (int i = 1; i < pl; ++i) {
        while (now != -1 && pat[now + 1] != pat[i]) now = pi[now];
        if (pat[now + 1] == pat[i]) ++now; pi[i] = now;
    }
    now = -1; vector<int> ind;
    for (int i = 0; i < sl; ++i) {
        while (now != -1 && pat[now + 1] != str[i]) now = pi[now];
        if (pat[now + 1] == str[i]) ++now;
        if (now == pl - 1) ind.push_back(i - pl + 1);
    }
    return ind;
}

// OR,
// creates a cyclic string of length k^n that contains every length n string as a substring. alphabet = [0, k - 1]
// O(k^n)
int ans[N], aux[N];
int de_bruijn(int k, int n) { // returns size (k^n)
    if (k == 1)
    {
        ans[0] = 0;
        return 1;
    }
    for (int i = 0; i < k * n; i++)
    {
        aux[i] = 0;
    }
    int sz = 0;
    function<void(int, int)> db = [&](int t, int p)
    {
        if (t > n)
        {
            if (n % p == 0)
            {
                for (int i = 1; i <= p; i++)
                {
                    ans[sz++] = aux[i];
                }
            }
        }
        else
        {
            aux[t] = aux[t - p];
            db(t + 1, p);
            for (int i = aux[t - p] + 1; i < k; i++)
            {
                aux[t] = i;
                db(t + 1, t);
            }
        }
    };
    db(1, 1);
    return sz;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k, n;
    cin >> k >> n;
    int len = de_bruijn(k, n);
    for (int i = 0; i < len; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}

// Z: O(|str| + |pat|)
// Application: Used to find all occurrences of a pattern in a text in linear time
lightoj.com/problem/substring-frequency

auto z(auto &str, auto &pat) {
	int pl = pat.size(); pat += '$' + str;
	int tl = pat.size(), Z[tl], l = 0, r = 0;
	for (int i = 1; i < tl; ++i) {
		if (i > r) {
			l = r = i;
			while (r < tl && pat[r - l] == pat[r]) ++r;
			Z[i] = r - l; --r;
		}
		else {
			if (Z[i - l] < r - i + 1) Z[i] = Z[i - l];
			else {
				l = i;
				while (r < tl && pat[r - l] == pat[r]) ++r;
				Z[i] = r - l; --r;
			}
		}
	}
    // return count(Z, Z + tl, pl);  // To determine the number of occurrences
    vector<int> ind;
	for (int i = 0; i < tl; ++i) {
		if (Z[i] == pl) ind.push_back(i - pl - 1);
	}
    return ind;
}

// OR,
// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1].
// The first entry of Z array is meaning less as complete string is always prefix of itself.

auto z(string &s) {
	int n = s.size(); vector<int> Z(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r) Z[i] = min(r - i + 1, Z[i - l]);
		while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) ++Z[i];
		if (i + Z[i] - 1 > r) l = i, r = i + Z[i] - 1;
	}
	return Z;
}

// Complextiy: make: O(|s|), count matches: O(|p|), find positions: O(r - l + 1), 1-based indexing
https://codeforces.com/problemset/problem/914/F
https://codeforces.com/problemset/problem/963/D

bitset<N> mask[26], oc;
void pre(string &s) {
    for (int i = 0; s[i]; ++i) mask[s[i] - 'a'][i] = true;
}
inline void up(string &s, int in, char ch) {
    --in; mask[s[in] - 'a'][in] = false;
    s[in] = ch; mask[s[in] - 'a'][in] = true;
}
int match(string &p, int l, int r) {
    int sz = p.size(); if (sz > r - l + 1) return 0; oc.set();
    for (int i = 0; p[i]; ++i) oc &= (mask[p[i] - 'a'] >> i);
    return (oc >> (l - 1)).count() - (oc >> (r - sz + 1)).count();
}
vector<int> posi(string &p, int l, int r) {
    int l1 = p.size(); if (l1 > r - l + 1) return {};
    vector<int> positions(match(p, l, r));
    int pos = oc._Find_next(l - 2), i = 0, l2 = positions.size();
    while (pos < r && i < l2) {
        positions[i++] = pos + 1; pos = oc._Find_next(pos);
    }
    return positions;
}

// OR,

bitset<N> mask[26], sMask;
void pre(string s) {
    s = "#" + s;
    for (int i = 1; s[i]; ++i) {
        int c = s[i] - 'a'; mask[c].set(i);
    }
}
inline void up(string &s, int in, char ch) {
    --in; mask[s[in] - 'a'][in] = false;
    s[in] = ch; mask[s[in] - 'a'][in] = true;
}
int match(string p, int l, int r) {
    int sz = p.size(); if (r - l + 1 < sz) return 0;
    p = "#" + p; sMask.set(); ++sz;
    for (int i = 1; i < sz; ++i) sMask &= (mask[p[i] - 'a'] >> i);
    return (sMask >> (l - 1)).count() - (sMask >> (r - sz + 2)).count(); // number of set bits from l to r
}
auto posi(string &p, int l, int r) {
    vector<int> positions(match(p, l, r));
    int in = 0, l1 = p.size(), l2 = positions.size();
    for (int i = l - 1; i < r - l1 + 2 && in < l2; ++i) {
        if (sMask[i]) positions[in++] = i + 1;
    }
    return positions;
}