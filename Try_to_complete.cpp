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
const ll M = 1e9 + 7, N = 2e5 + 5;

struct Trie {
    bool isWord;
    int cnt;                          // Count of words with a specific prefix
    map<char, Trie*> mp;
    int maxFreq;                      // Max frequency in this subtree
    string maxString;                 // Most frequent string in this subtree
    Trie() : isWord(false), cnt(0), maxFreq(0), maxString("") {}
    ~Trie() {                         // Destructor to delete all child nodes
        for (auto& p : mp) delete p.second;
    }
};

Trie* Node() {
    return new Trie;
}

void ins(Trie*& head, const string& str) {
    if (head == nullptr) head = Node();
    Trie* cur = head;
    string currentString;
    for (char ch : str) {
        currentString += ch;
        if (cur->mp.find(ch) == cur->mp.end())
            cur->mp[ch] = Node();
        cur = cur->mp[ch];
        cur->cnt++;                   // Increment prefix count

        // Update most frequent string with prefix ending at this node
        if (cur->cnt > cur->maxFreq || (cur->cnt == cur->maxFreq && currentString < cur->maxString)) {
            cur->maxFreq = cur->cnt;
            cur->maxString = currentString;
        }
    }
    cur->isWord = true;
}

pair<string, int> mstfre(Trie* head, const string& prefix) {
    if (head == nullptr) return {"", -1};
    Trie* cur = head;
    for (char ch : prefix) {
        if (cur->mp.find(ch) == cur->mp.end()) return {"", -1};  // Prefix not found
        cur = cur->mp[ch];
    }
    // The node `cur` represents the end of the prefix
    if (cur->maxFreq > 0)
        return {cur->maxString, cur->maxFreq};
    return {"", -1};
}

Trie* t = nullptr;

void reset() {
    delete t;
    t = nullptr;
}

// int main() {
//     int n;
//     cin >> n;
//     t = Node();
//     for (int i = 0; i < n; i++) {
//         string word;
//         cin >> word;
//         ins(t, word);
//     }

//     int q;
//     cin >> q;
//     for (int i = 0; i < q; i++) {
//         string prefix;
//         cin >> prefix;
//         auto result = mstgre(t, prefix);
//         if (result.second == -1) cout << "-1\n";
//         else cout << result.first << " " << result.second << "\n";
//     }

//     reset();
//     return 0;
// }


void test(int tc) {
    ll n = 0, m = 0, a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, q = 0;
    cin >> n;
    // vector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }
    while(n--) {
        string s; cin >> s;
        ins(t, s);
    }
    cin >> q;
    while(q--) {
        string s; cin >> s;
        auto [str, freq] = mstfre(t, s);
        if (freq == -1) cout << -1 << '\n';
        else cout << str << ' ' << freq << '\n';
    }
    // cout << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
    int tc = 0, t = 1;
    // cin >> t;
    while (tc < t) test(++tc);
    return 0;
}