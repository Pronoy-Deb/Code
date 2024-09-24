// Complexity: push_back(), pop_back(), Deletion, Replace: O(log n), Insertion: O(n), Concatenation: O(1)

// Inclusions:
#include <ext/rope>
using namespace __gnu_cxx;

// Declaration & Operation:
    rope<int> rp;
    rp.push_back(10);
    for (auto &e : rp) cout << e << ' ';

// Example:
    cin >> n >> m; rope <int> rp;
    for (i = 1; i <= n; ++i) rp.push_back(i);
    for (i = 0; i < m; ++i) {
        int l, r; cin >> l >> r; --l, --r;
        rope <int> cur = rp.substr(l, r - l + 1);
        rp.erase(l, r - l + 1);
        rp.insert(rp.mutable_begin(), cur);
    }
    for (auto it = rp.mutable_begin(); it != rp.mutable_end(); ++it)
        cout << *it << ' ';