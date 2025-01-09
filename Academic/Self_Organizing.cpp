#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "Enter the number of elements: ";
    int n; cin >> n; list<int> ls;
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        int ele; cin >> ele;
        ls.push_back(ele);
    }
    cout << "Enter the number of variables: ";
    int m; cin >> m;
    while (m--) {
        cout << "Enter the variable: ";
        int var; cin >> var;
        ls.remove(var);
        ls.push_front(var);
        cout << "The current list is: ";
        for (auto e : ls) cout << e << ' '; cout << endl;
    }
    return 0;
}