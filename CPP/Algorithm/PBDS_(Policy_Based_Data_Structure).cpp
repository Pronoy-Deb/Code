// PBDS or Order set / multiset / map any operation O(log(n))
// insert, erase, size, order_of_key, find_by_order
// 2) In multiset, lower_bound works as upper_bound and vice-versa
// 3) Write after "using namespace std":
// 4) Don't use .find() for multiset, because it will always return .end()
Note: 1) Use less_equal<> instead of less<> to use it like a multiset

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Declaration: oset<long long> st;

// OR,

typedef tree<long long, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> oset;

// Declaration: oset st;

// For using as map:

template <typename T, typename R> using omap = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Declaration: omap<int, int> mp;

// For using as minheap:

using minheap = priority_queue<long long, vector<long long>, greater<long long>>;
typedef tree<int, null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// Operation:
    for (int i = 1; i <= 10; ++i) {
        long long a; cin >> a; st.insert(a);
    }

    // Deleting 2 from only the SET if it exists
    auto it = st.find(2);
    if (it != st.end()) st.erase(it);

    // Deleting 2 from the multiset
    st.erase(st.upper_bound(ar[j]));
    OR, st.erase(st.find_by_order(st.order_of_key(2)));

    // Finding the 2-nd element in the set (random access using index)
    cout << *st.find_by_order(1);

    // Number of elements strictly less than k = 4
    cout << st.order_of_key(4);

// Problem: https://cses.fi/problemset/task/1076

// PBDS for Trie:
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>

using namespace __gnu_pbds;

template<class T> using pref_trie = trie<T, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update>;

// Declaration: pref_trie<string> base;

// OR,

typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> pref_trie;

// Declaration: pref_trie base;

// Example:
    pref_trie<string> base; base.insert("sun");
    string x; cout << x.substr(1) << '\n';
    auto range = base.prefix_range(x.substr(1));
    cout << range.first << ' ' << range.second << '\n';

// For integer supported trie:

struct int_access_traits {
    static constexpr int min_value() { return 0; }
    static constexpr int max_value() { return 9; }
    template <typename T> static auto child_key(const T& value, size_t pos) {
        return (value / static_cast<int>(pow(10, pos))) % 10;
    }
    template <typename T> static size_t size(const T& value) {
        return value == 0 ? 1 : static_cast<size_t>(log10(value) + 1);
    }
};

template<class T> using int_trie = trie<T, null_type, int_access_traits, pat_trie_tag, trie_prefix_search_node_update>;