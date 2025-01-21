#include <iostream>
#include <stack>
#include <vector>
using namespace std;

auto mxmn(auto &v) {
    stack<int> sk; int n = v.size(), len[n];
    for (int i = 0; i < n; ++i) {
        while (!sk.empty() && v[sk.top()] >= v[i]) {
            int top = sk.top(); sk.pop();
            len[top] = sk.empty() ? i : i - sk.top() - 1;
        }
        sk.push(i);
    }
    while (!sk.empty()) {
        int top = sk.top(); sk.pop();
        len[top] = sk.empty() ? n : n - sk.top() - 1;
    }
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        int ws = len[i] - 1; res[ws] = max(res[ws], v[i]);
    }
    for (int i = n - 2; i >= 0; --i) res[i] = max(res[i], res[i + 1]);
    return res;
}

// Driver program
int main() {
    vector<int> v = { 10, 20, 30, 50, 10, 70, 30 };
    vector<int> res = mxmn(v);
    for (int x : res)
        cout << x << " ";
    return 0;
}