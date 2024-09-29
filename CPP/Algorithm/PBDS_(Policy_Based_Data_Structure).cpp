// PBDS or Order set / multiset / map any operation O(log(n))
// insert, erase, size, order_of_key, find_by_order
// 2) In multiset, lower_bound works as upper_bound and vice-versa
// 3) Write after "using namespace std":
Note: 1) Use less_equal<> instead of less<> to use it like a multiset

#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ost = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

Declaration: ost<long long> st;

// OR,

typedef tree<long long, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ost;

Declaration: ost st;

// For using as map:

template<class key, class value, class cmp = less<key>>
using omp = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

Declaration: omp<int, int> mp;

// For using as minheap:

using minheap = priority_queue<long long, vector<long long>, greater<long long>>;
typedef tree<int, null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// Operation:
    for (int i = 1; i <= 10; ++i) {
        long long a; cin >> a; st.insert(a);
    }

    // Deleting 2 from the set if it exists
    auto it = st.find(2);
    if (it != st.end()) st.erase(it);

    // Deleting 2 from the multiset
    st.erase(st.upper_bound(ar[j]));
    OR, st.erase(st.find_by_order(st.order_of_key(2)));

    // Finding the second element in the set (random access using index)
    cout << *st.find_by_order(1);

    // Number of elements strictly less than k = 4
    cout << st.order_of_key(4);

// Problem: https://cses.fi/problemset/task/1076