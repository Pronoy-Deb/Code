// Complexity: O(n)
// Index of Next Nearest Greater Element:

long long ar[N], nng[N], n;
void pre() {
    stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] > ar[sk.top()]) {
            nng[sk.top()] = i; sk.pop();
        }
        sk.emplace(i);
    }
    while (!sk.empty()) {
        nng[sk.top()] = -1; sk.pop();
    }
}

// Index of Next Nearest Smaller Element:

long long ar[N], nns[N], n;
void pre() {
    stack<long long> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && ar[i] < ar[sk.top()]) {
            nns[sk.top()] = i; sk.pop();
        }
        sk.emplace(i);
    }
    while (!sk.empty()) {
        nng[sk.top()] = -1; sk.pop();
    }
}

// Index of Next Farthest Greater Element:



// Operation:
    cin >> n;
    for (i = 0; i < n; ++i) { cin >> ar[i]; }
    pre();
    for (i = 0; i < n; ++i) cout << (nng[i] == -1 ? -1 : ar[nng[i]]) << ' ';


// Index of Previous Nearest Smaller Element:

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