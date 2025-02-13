https://codeforces.com/contest/706/problem/D

const int L = 31;
int trie[N * L][2], cnt[N * L], tot = 1;
void ins(int x) {
    int u = 1;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (!trie[u][f]) trie[u][f] = ++tot;
        u = trie[u][f]; ++cnt[u];
    }
}
void rem(int x) {
    int u = 1;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1; u = trie[u][f]; --cnt[u];
    }
}
int mxxr(int x) { // maximum of val ^ x
    int u = 1, res = 0;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (cnt[trie[u][!f]]) res |= 1 << i, u = trie[u][!f];
        else u = trie[u][f];
    }
    return res;
}
int mnxr(int x) { // minimum of val ^ x
    int u = 1, res = 0;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (cnt[trie[u][f]]) u = trie[u][f];
        else res |= 1 << i, u = trie[u][!f];
    }
    return res;
}
int get(int x, int k) { // no of values s.t. val ^ x < k
    int u = 1, ans = 0;
    for (int i = L - 1; u and i >= 0; --i) {
        int f1 = x >> i & 1, f2 = k >> i & 1;
        if (f2 == 1) {
            if (trie[u][f1]) ans += cnt[trie[u][f1]];
            u = trie[u][!f1];
        }
        else u = trie[u][f1];
    }
    return ans;
}

// OR: Inserts, erases and searches strings in the trie in O(sz)
https://www.spoj.com/problems/ADAINDEX/

struct Trie {
    bool isWord; int cnt;
    map<char, Trie*> mp;
    Trie() : isWord(false), cnt(0) {}
    ~Trie() { for (auto& p : mp) delete p.second; }
};
Trie* Node() { return new Trie; }
int dis = 0;
void ins(Trie*& head, const char* str) {
    if (head == nullptr) head = Node(); Trie* cur = head;
    while (*str) {
        if (cur->mp.find(*str) == cur->mp.end()) cur->mp[*str] = Node();
        cur = cur->mp[*str]; cur->cnt++; ++str;
    }
    if (!cur->isWord) {
        cur->isWord = true; ++dis;
    }
}
bool haveChild(Trie const* cur) {
    for (auto it : cur->mp) {
        if (it.second != nullptr) return true;
    }
    return false;
}
bool rem(Trie*& cur, const char* str) {
    if (cur == nullptr) return false;
    if (*str) {
        if (cur->mp.find(*str) != cur->mp.end() &&
            rem(cur->mp[*str], str + 1) && cur->isWord == false) {
            if (!haveChild(cur)) {
                delete cur; cur = nullptr; return true;
            }
            return false;
        }
    }
    if (*str == '\0' && cur->isWord) {
        if (!haveChild(cur)) {
            cur->isWord = false; dis--; delete cur;
            cur = nullptr; return true;
        }
        else {
            cur->isWord = false; --dis; return false;
        }
    }
    return false;
}
bool get(Trie* head, const char* str) { // Checking the presence of a string
    if (head == nullptr) return false;
    Trie* cur = head;
    while (*str) {
        cur = cur->mp[*str]; if (cur == nullptr) return false; ++str;
    }
    return cur->isWord;
}
int cnt(Trie* head, const char* c) { // Counting the number of strings with a prefix "c"
    if (head == nullptr) return 0; Trie* cur = head;
    while (*c) {
        cur = cur->mp[*c]; if (cur == nullptr) return 0; ++c;
    }
    return cur->cnt;
}
Trie* t = nullptr;
void reset() { delete t; t = nullptr; dis = 0; }

// Operation:
    cin >> n >> q;
    while (n--) {
        string s; cin >> s; ins(t, s.c_str());
    }
    while (q--) {
        string s; cin >>s; cout << cnt(t, s.c_str()) << '\n';
    }

// Persistent Trie:
// find maximum value (x ^ a[j]) in the range (l,r) where l<=j<=r

const int N = 1e5 + 100, K = 15;
struct node_t; typedef node_t *node_p;
struct node_t {
    int time; node_p to[2];
    node_t() : time(0) { to[0] = to[1] = 0; }
    bool go(int l) const {
        if (!this) return false; return time >= l;
    }
    node_p clone() {
        node_p cur = new node_t();
        if (this) {
            cur->time = time; cur->to[0] = to[0]; cur->to[1] = to[1];
        }
        return cur;
    }
};
node_p last, version[N];
void ins(int a, int time) {
    node_p v = version[time] = last = last->clone();
    for (int i = K - 1; i >= 0; --i) {
        int bit = (a >> i) & 1; node_p &child = v->to[bit];
        child = child->clone(); v = child; v->time = time;
    }
}
int get(node_p v, int x, int l) {
    int ans = 0;
    for (int i = K - 1; i >= 0; --i) {
        int bit = (x >> i) & 1;
        if (v->to[bit]->go(l)) { // checking if this bit was inserted before the range
            ans |= 1 << i; v = v->to[bit];
        }
        else v = v->to[bit ^ 1];
    }
    return ans;
}

// Operation:
    cin >> n >> q;
    last = 0;
    for (i = 0; i < n; ++i) {
        cin >> a; ins(a, i);
    }
    while (q--) {
        int x, l, r; cin >> x >> l >> r; --l, --r;
        cout << get(version[r], ~x, l) << '\n'; // Trie version[r] contains the trie for [0...r] elements
    }