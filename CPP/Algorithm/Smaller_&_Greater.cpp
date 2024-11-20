// Index of Next Nearest Greater Element: O(n)

auto NNG(auto &ar) {
    int n = ar.size(); vector<int> nng(n, -1); stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] > ar[sk.top()]) {
            nng[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    return nng;
}

// Index of Next Nearest Smaller Element: O(n)

auto NNS(auto &ar) {
    int n = ar.size(); vector<int> nns(n, -1); stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] < ar[sk.top()]) {
            nns[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
}

// Index of Next Farthest Greater Element: O(n*logn)

auto NFG(auto &ar) {
    int n = ar.size(); vector<int> nfg(n, -1);
	map<int, stack<int>> mp;
	for (int i = 0; i < n; ++i) mp[ar[i]].push(i);
	for (int i = n - 1; i >= 0; --i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f >= ar[i]) break;
            while (!s.empty()) {
                nfg[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (nfg[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return nfg;
}

// Index of Next Farthest Smaller Element: O(n*logn)

auto NFS(auto &ar) {
    int n = ar.size(); vector<int> nfs(n, -1);
	map<int, stack<int>, greater<>> mp;
	for (int i = 0; i < n; ++i) mp[ar[i]].push(i);
	for (int i = n - 1; i >= 0; --i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f <= ar[i]) break;
            while (!s.empty()) {
                nfs[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (nfs[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return nfs;
}

// Index of Previous Nearest Greater Element: O(n)

auto PNG(auto &ar) {
    int n = ar.size(); vector<int> png(n, -1); stack<long long> sk;
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && ar[i] > ar[sk.top()]) {
            png[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    return png;
}

// Index of Previous Nearest Smaller Element: O(n)

auto PNS(auto &ar) {
    int n = ar.size(); vector<int> pns(n, -1); stack<long long> sk;
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && ar[i] < ar[sk.top()]) {
            pns[sk.top()] = i; sk.pop();
        }
        sk.push(i);
    }
    return pns;
}

// Index of Previous Farthest Greater Element: O(n*logn)

auto PFG(auto &ar) {
    int n = ar.size(); vector<int> pfg(n, -1);
	map<int, stack<int>> mp;
	for (int i = n - 1; i >= 0; --i) mp[ar[i]].push(i);
	for (int i = 0; i < n; ++i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f >= ar[i]) break;
            while (!s.empty()) {
                pfg[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (pfg[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return pfg;
}

// Index of Previous Farthest Smaller Element: O(n*logn)

auto PFS(auto &ar) {
    int n = ar.size(); vector<int> pfs(n, -1);
	map<int, stack<int>, greater<>> mp;
	for (int i = n - 1; i >= 0; --i) mp[ar[i]].push(i);
	for (int i = 0; i < n; ++i) {
		if (mp.empty()) break;
        auto it = mp.begin();
        while (it != mp.end()) {
            auto &[f, s] = *it;
            if (f <= ar[i]) break;
            while (!s.empty()) {
                pfs[s.top()] = i; s.pop();
            }
            if (s.empty()) it = mp.erase(it);
            else ++it;
        }
        if (pfs[i] == -1) {
            int sz = mp[ar[i]].size();
            if (sz > 0) mp[ar[i]].pop();
            if (sz == 1) mp.erase(ar[i]);
        }
    }
    return pfs;
}