// Complexity: O(|s|)
// Iterative Approach:
// Work: Works for all types of strings / brackets

bool bb(auto &s) {
    int o1 = 0, o2 = 0, o3 = 0;
    for (auto &i : s) {
        if (o1 < 0 or o2 < 0 or o3 < 0) return 0;
        i == '(' ? o1++ : i == '{' ? o2++ : i == '[' ? o3++ : i == ')' ? o1-- : i == '}' ? o2-- : o3--;
    }
    return (!o1 && !o2 && !o3);
}

// Stack Approach:
// Work: Works only for "{[()]}" this type of a string, not "{[(})]" this

bool bb(auto &s) {
    map<char, int> mp = {{'(', -1}, {'{', -2}, {'[', -3}, {')', 1}, {'}', 2}, {']', 3}};
    stack<char> sk;
    for (auto &i : s) {
        if (mp[i] < 0) sk.emplace(i);
        else {
            if (sk.empty()) return false;
            if (mp[sk.top()] + mp[i]) return false;
            sk.pop();
        }
    }
    return sk.empty();
}

// Balanced Bracket Tree:
// There is a directed edge from bracket i to bracket j if j is directly inside i
vector<int> g[N]; int sz[N];
void dfs(int u) {
    sz[u] = 1;
    for (auto &v : g[u]) {
        dfs(v); sz[u] += sz[v];
    }
}

// Operation:
    cin >> k; string s; cin >> s;
    int bid = 0; vector<int> rts, v;
    for (auto &c : s) {
        if (c == '(') v.push_back(++bid);
        else {
            int cur_bid = v.back(); v.pop_back();
            if (!v.empty()) g[v.back()].push_back(cur_bid);
            else rts.push_back(cur_bid);
        }
    }
    for (auto &r : rts) dfs(r);
    sort(sz + 1, sz + bid + 1);
    int64_t ans = 0;
    for (i = 1; i <= bid - k; ++i) ans += sz[i] - 1;
    cout << ans << '\n';
    for (i = 1; i <= bid; ++i) g[i].clear();

// Problem: https://codeforces.com/contest/1821/problem/E