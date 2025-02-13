#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int w;
    bool operator>(const Node &other) const { return w > other.w; }
};

template <typename T>
struct PQ
{
    int64_t sum = 0;
    priority_queue<T, vector<T>, greater<T>> Q;

    void push(T x)
    {
        x.w -= sum;
        Q.push(x);
    }

    T pop()
    {
        auto ans = Q.top();
        Q.pop();
        ans.w += sum;
        return ans;
    }

    int size() { return Q.size(); }

    void add(int64_t x) { sum += x; }

    void merge(PQ &&x)
    {
        if (size() < x.size())
            swap(sum, x.sum), swap(Q, x.Q);
        while (x.size())
        {
            auto tmp = x.pop();
            tmp.w -= sum;
            Q.push(tmp);
        }
    }
};

PQ<Node> mexPQ;      // Tracks missing numbers (MEX candidates)
unordered_set<int> present; // Tracks present numbers
int water_level = 0; // Global XOR shift

void add(int v)
{
    if (!present.count(v))
        mexPQ.push({v});
    present.insert(v);
}

void updateAll(int v)
{
    water_level ^= v; // Apply XOR globally
    mexPQ.add(v);
}

int getMin()
{
    while (present.count(mexPQ.Q.top().w ^ water_level))
    {
        mexPQ.pop();
    }
    return mexPQ.Q.top().w ^ water_level; // Return actual MEX
}

void test(int32_t tc)
{
    int64_t n, q;
    cin >> n >> q;

    vector<int64_t> ar(n);
    present.clear();
    while (!mexPQ.Q.empty())
        mexPQ.Q.pop(); // Clear priority queue
    mexPQ.sum = 0;
    water_level = 0;

    for (int i = 0; i < n; ++i)
    {
        cin >> ar[i];
        present.insert(ar[i]); // Track present numbers
    }

    // Populate missing numbers (MEX candidates)
    for (int i = 0; i <= n + q; ++i)
    {
        if (!present.count(i))
            add(i);
    }

    while (q--)
    {
        int x;
        cin >> x;
        updateAll(x);
        cout << getMin() << '\n'; // Print correct MEX
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int32_t tt = 1;
    // cin >> tt;
    for (int32_t tc = 1; tc <= tt; ++tc)
    {
        test(tc);
    }
    return 0;
}


// #include <bits/stdc++.h>
// using namespace std;
// #ifdef LOCAL
// #include "def.h"
// #else
// #define ck(...)
// #endif
// #define ps(b) cout << (b ? "YES" : "NO") << '\n'
// const int64_t M = 1e9 + 7, N = 3e5 + 5;

// multiset<int> S;
// int water_level = 0;

// void add(int v) {
//     S.insert(v ^ water_level); // XOR with global shift
// }

// void remove(int v) {
//     auto it = S.find(v ^ water_level);
//     if (it != S.end()) S.erase(it);
// }

// void updateAll(int v) {
//     water_level ^= v; // Global XOR shift
// }

// int getMin() {
//     while (S.count(*S.begin() ^ water_level)) {
//         S.erase(*S.begin());
//     }
//     return *S.begin() ^ water_level; // Return correct MEX
// }

// int size() {
//     return S.size();
// }

// void test(int32_t tc) {
//     int64_t n, q; cin >> n >> q;
//     vector<int64_t> ar(n); bool vis[2 * N]{};
//     for (int i = 0; i < n; ++i) { cin >> ar[i]; vis[ar[i]] = 1; }
//     for (int i = 0; i < 2 * N; ++i) {
//         if (!vis[i]) add(i);
//     }
//     // int ans = 0;
//     while (q--) {
//         int x; cin >> x;
//         // ans ^= x;
//         updateAll(x);
//         cout << getMin();
//         cout << '\n';
//     }
// }

// int32_t main() {
//     cin.tie(0)->sync_with_stdio(0); cin.exceptions(ios::failbit | ios::badbit);
//     int32_t tc = 0, tt = 1;
//     // cin >> tt;
//     while (tc++ < tt) test(tc);
//     return 0;
// }