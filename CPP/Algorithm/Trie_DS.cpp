// Trie DS: O()
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
int mx_xr(int x) { // maximum of val ^ x
    int u = 1, res = 0;
    for (int i = L - 1; i >= 0; --i) {
        int f = x >> i & 1;
        if (cnt[trie[u][!f]]) res |= 1 << i, u = trie[u][!f];
        else u = trie[u][f];
    }
    return res;
}
int mn_xr(int x) { // minimum of val ^ x
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

// Another Approach:
// Note: Inserts, erases and searches strings in the trie

struct Trie {
    bool isWord;
    map<char, Trie*> mp;
};
Trie* newNode() {
    Trie* nd = new Trie; nd->isWord = false; return nd;
}
auto up(Trie*& head, const char* str) {
    if (head == nullptr) head = newNode();
    Trie* cur = head;
    while (*str) {
        if (cur->mp.find(*str) == cur->mp.end())
            cur->mp[*str] = newNode();
        cur = cur->mp[*str]; ++str;
    }
    cur->isWord = true;
}
auto haveChild(Trie const* cur) {
    for (auto it: cur->mp) {
        if (it.second != nullptr) return true;
    }
    return false;
}
auto del(Trie* &cur, const char* str) {
    if (cur == nullptr) return false;
    if (*str) {
        if (cur!=nullptr && cur->mp.find(*str)!=cur->mp.end() && del(cur->mp[*str],str+1) && cur->isWord==false) {
            if (!haveChild(cur)) {
                delete cur; cur = nullptr; return true;
            }
            else return false;
        }
    }
    if (*str == '\0' && cur->isWord) {
        if (!haveChild(cur)) {
            delete cur; cur = nullptr; return true;
        }
        else {
            cur->isWord = false; return false;
        }
    }
    return false;
}
auto get(Trie* head, const char* str) {
    if (head == nullptr) return false;
    Trie* cur = head;
    while (*str) {
        cur = cur->mp[*str]; if (cur == nullptr) return false; ++str;
    }
    return cur->isWord;
}

// Operation:
    Trie* t = nullptr;
    up(t, "hello");
    cout << get(t, "hello") << " ";  // prints 1
    up(t, "helloworld");
    cout << get(t, "helloworld") << " ";  // prints 1
    cout << get(t, "helll") << " ";  // prints 0 (Not present)
    up(t, "hell");
    cout << get(t, "hell") << " ";  // prints 1
    up(t, "h");
    cout << get(t, "h") << endl;  // prints 1 + newline
    del(t, "hello");
    cout << get(t, "hello") << " ";  // prints 0 (`hello` deleted)
    cout << get(t, "helloworld") << " ";  // prints 1
    cout << get(t, "hell") << endl;  // prints 1 + newline
    del(t, "h");
    cout << get(t, "h") << " ";  // prints 0 (`h` deleted)
    cout << get(t, "hell") << " ";  // prints 1
    cout << get(t, "helloworld") << endl;  // prints 1 + newline
    del(t, "helloworld");
    cout << get(t, "helloworld") << " ";  // prints 0
    cout << get(t, "hell") << " ";  // prints 1
    del(t, "hell");
    cout << get(t, "hell") << endl;  // prints 0 + newline
    if (t == nullptr)
    cout << "Trie empty!!\n";  // Trie is empty now
    cout << get(t, "hell");  // prints 0