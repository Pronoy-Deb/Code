#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#include "def.h"
#else
#define ck(...)
#endif
#define ll long long
#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
const ll M = 1e9 + 7, N = 1500 + 5;

struct Trie {
    bool isWord; int cnt; map<char, Trie*> mp;
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

void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    // cin >> n;
    string s; cin >> s;
    string r; cin >> r;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    cin >> k;
    n = s.size();
    for (i = 0; i < n; ++i) {
        string tm; c = 0;
        for (j = i; j < n; ++j) {
            c += (r[s[j] - 'a'] == '0');
            if (c > k) break;
            tm += s[j];
            ins(t, tm.c_str());
        }
    }
    cout << dis << '\n';
    // reset();
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}