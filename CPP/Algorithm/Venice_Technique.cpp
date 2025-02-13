// https://codeforces.com/problemset/problem/923/B

template <typename T> struct vset {
	multiset<T> S; int64_t wlvl = 0;
	inline void insert(T v) { S.insert(v + wlvl); }
	inline auto erase(T v) {
        auto it = S.find(v + wlvl); return (it == S.end() ? it : S.erase(it));
    }
	inline void upal(T v) { wlvl += v; } // For Subtracting
	inline int64_t min() { return (S.empty() ? LLONG_MIN : *S.begin() - wlvl); }
    inline int64_t max() { return (S.empty() ? LLONG_MAX : *prev(S.end()) - wlvl); }
    inline bool empty() { return S.empty(); }
	inline int size() { return S.size(); }
};

// Operation:
    int64_t n; cin >> n;
    vector<int64_t> v(n), t(n);
    for (int i = 0; i < n; ++i) { cin >> v[i]; }
    for (int i = 0; i < n; ++i) { cin >> t[i]; }
    vset<int64_t> st;
    for (int i = 0; i < n; ++i) {
        st.insert(v[i]); st.upal(t[i]);
        int64_t tot = t[i] * st.size(), mn = st.min();
        while (!st.empty() && mn <= 0) {
            tot -= abs(mn); st.erase(mn); mn = st.min();
        }
        cout << tot << ' ';
    }

// OR,

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