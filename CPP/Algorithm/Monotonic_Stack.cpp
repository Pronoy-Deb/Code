// Index of Next Nearest Greater Element: O(n)

auto nng(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1); stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] > ar[sk.top()]) {
            v[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    return v;
}

// Index of Next Nearest Smaller Element: O(n)

auto nns(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1); stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] < ar[sk.top()]) {
            v[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
}

// Index of Next Farthest Greater Element: O(n*logn)

auto nfg(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1);
	map<int, stack<int>> mp;
	for (int i = 0; i < n; ++i) mp[ar[i]].push(i);
	for (int i = n - 1; i >= 0; --i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f >= ar[i]) break;
            while (!s.empty()) {
                v[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (v[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return v;
}

// Index of Next Farthest Smaller Element: O(n*logn)

auto nfs(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1);
	map<int, stack<int>, greater<>> mp;
	for (int i = 0; i < n; ++i) mp[ar[i]].push(i);
	for (int i = n - 1; i >= 0; --i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f <= ar[i]) break;
            while (!s.empty()) {
                v[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (v[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return v;
}

// Index of Previous Nearest Greater Element: O(n)

auto png(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1); stack<long long> sk;
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && ar[i] > ar[sk.top()]) {
            v[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    return v;
}

// Index of Previous Nearest Smaller Element: O(n)

auto pns(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1); stack<long long> sk;
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && ar[i] < ar[sk.top()]) {
            v[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    return v;
}

// Index of Previous Farthest Greater Element: O(n*logn)

auto pfg(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1);
	map<int, stack<int>> mp;
	for (int i = n - 1; i >= 0; --i) mp[ar[i]].push(i);
	for (int i = 0; i < n; ++i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f >= ar[i]) break;
            while (!s.empty()) {
                v[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (v[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return v;
}

// Index of Previous Farthest Smaller Element: O(n*logn)

auto pfs(auto &ar) {
    int n = ar.size(); vector<int> v(n, -1);
	map<int, stack<int>, greater<>> mp;
	for (int i = n - 1; i >= 0; --i) mp[ar[i]].push(i);
	for (int i = 0; i < n; ++i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f <= ar[i]) break;
            while (!s.empty()) {
                v[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (v[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return v;
}

// Next Smaller of Next Greater: O(n)

auto nge(auto &ar, char ord) {
	stack<int> S; int n = ar.size(); vector<int> next(n);
	for (int i = n - 1; i >= 0; --i) {
        while (!S.empty() && ((ord == 'G') ? ar[S.top()] <= ar[i] : ar[S.top()] >= ar[i])) S.pop();
		next[i] = S.empty() ? -1 : S.top(); S.push(i);
	}
    return next;
}
auto nsng(auto &ar) {
    auto ng = nge(ar, 'G'), rs = nge(ar, 'S');
    int n = ar.size(); vector<int> ans(n);
	for (int i = 0; i < n; ++i) ans[i] = (ng[i] != -1 && rs[ng[i]] != -1) ? ar[rs[ng[i]]] : -1;
    return ans;
}

// Next Greater Frequency Element

auto ngf(auto &v) {
	stack<pair<int, int>> sk; map<int, int> mp;
	int n = v.size(); vector<int> res(n);
	for (auto e : v) ++mp[e]; int fre = mp[v[n - 1]];
	sk.push({v[n - 1], fre}); res[n - 1] = -1;
	for (int i = n - 2; i >= 0; --i) {
		fre = mp[v[i]];
		while (!sk.empty() && fre >= sk.top().second) sk.pop();
		res[i] = sk.empty() ? -1 : sk.top().first;
		sk.push({v[i], fre});
	}
	return res;
}

// Sum of Max of all Subarrays

int64_t mxsum(auto &v) {
    stack<int> sk; int64_t n = v.size(), res = 0;
    for (int i = 0; i < n; ++i) {
        while (!sk.empty() && v[sk.top()] < v[i]) {
            int j = sk.top(); sk.pop();
            int64_t l = sk.empty() ? j + 1 : j - sk.top(), r = i - j;
            res += v[j] * l * r;
        }
        sk.push(i);
    }
    while (!sk.empty()) {
        int j = sk.top(); sk.pop();
        int64_t l = sk.empty() ? j + 1 : j - sk.top(), r = n - j;
        res += v[j] * l * r;
    }
    return res;
}

// Largest Rectangular Area in a Histogram

int lra(auto &v) {
    stack<int> sk; int64_t n = v.size(), res = 0;
    for (int i = 0; i < n; ++i) {
        while (!sk.empty() && v[sk.top()] >= v[i]) {
            int j = sk.top(); sk.pop();
            int64_t l = sk.empty() ? i : i - sk.top() - 1;
            res = max(res, v[j] * l);
        }
        sk.push(i);
    }
    while (!sk.empty()) {
        int j = sk.top(); sk.pop();
        int64_t l = sk.empty() ? n : n - sk.top() - 1;
        res = max(res, v[j] * l);
    }
    return res;
}

// Lexicographically largest subsequence containing all distinct characters only once

string lls(string &s) {
	stack<char> sk; bool vis[26]{}; int cnt[26]{}, n = s.size();
	for (auto c : s) ++cnt[c - 'a'];
	for (int i = 0; i < n; ++i) {
		--cnt[s[i] - 'a']; if (vis[s[i] - 'a']) continue;
		while (!sk.empty() && sk.top() < s[i] && cnt[sk.top() - 'a']) {
			vis[sk.top() - 'a'] = false; sk.pop();
		}
		sk.push(s[i]); vis[s[i] - 'a'] = true;
	}
	string S; while (!sk.empty()) { S += sk.top(); sk.pop(); }
	reverse(S.begin(), S.end()); return S;
}

// Maximum of minimums of every window size [1, n] in a given array

auto mxmn(auto &v) {
    stack<int> sk; int n = v.size(), len[n];
    for (int i = 0; i < n; ++i) {
        while (!sk.empty() && v[sk.top()] >= v[i]) {
            int top = sk.top(); sk.pop();
            len[top] = sk.empty() ? i : i - sk.top() - 1;
        }
        sk.push(i);
    }
    while (!sk.empty()) {
        int top = sk.top(); sk.pop();
        len[top] = sk.empty() ? n : n - sk.top() - 1;
    }
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        int ws = len[i] - 1; res[ws] = max(res[ws], (int)v[i]);
    }
    for (int i = n - 2; i >= 0; --i) res[i] = max(res[i], res[i + 1]);
    return res;
}