// Complexity: O(n)
// Next Greater Element:

long long ar[N], ng[N], n;
void pre() {
    stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] > ar[sk.top()]) {
            ng[sk.top()] = i; sk.pop();
        }
        sk.emplace(i);
    }
    while (!sk.empty()) {
        ng[sk.top()] = -1; sk.pop();
    }
}

// Operation:
    cin >> n;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    pre();
    for (i = 0; i < n; ++i) cout << (ng[i] == -1 ? -1 : ar[ng[i]]) << ' ';

// Previous Smaller Element:

long long ar[N], ps[N], n;
void pre() {
    stack<long long> sk;
    for (i = n - 1; i >= 0; --i) {
        while (!sk.empty() && ar[i] < ar[sk.top()]) {
            ps[sk.top()] = i; sk.pop();
        }
        sk.emplace(i);
    }
    while (!sk.empty()) {
        ps[sk.top()] = -1; sk.pop();
    }
}

// Operation:
    cin >> n;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    pre();
    for (i = 0; i < n; ++i) cout << (ps[i] == -1 ? -1 : ar[ps[i]]) << ' ';