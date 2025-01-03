#include<bits/stdc++.h>
using namespace std;

int precedence(string c) {
//    cout << c << '\n';
    if (c == "^") return 4;
    if (c == "/" or c == "*") return 3;
    if (c == "+" or c == "-") return 2;
    else return 1;
}

int operation(int b, int a, char c) {
    if (c == '+') return a + b;
    if (c == '-') return a - b;
    if (c == '*') return a * b;
    if (c == '/') return a / b;
    else return pow(a, b);
}

int stoint(string s) {
    int n = 0;
    for (auto c : s) {
        n = n * 10 + (c - '0');
    }
    return n;
}

int main() {
    cout << "Enter the space separated expression: ";
    string s; getline(cin, s);
//    cout << s << endl; 2 + 3 + 4    (2 * 6 / 3) - (3 * 1)
    string postfix;
    stack<string> sk; int c = 0;
    while (c < s.size()) {
        if (s[c] == ' ') {
            ++c; continue;
        }
        string st;
        while (isalnum(s[c])) {
            st.push_back(s[c]); ++c;
        }
        if (!st.empty()) {
            postfix += st; postfix.push_back(' ');
        }
        else {
            string r = s[c];
            if (r == "-" and isalnum(s[c + 1])) {
                st.clear(); st.push_back('-'); ++c;
                while (isalnum(s[c])) {
                    st.push_back(s[c]); ++c;
                }
                postfix += st; postfix.push_back(' ');
                continue;
            }
            if (sk.empty() or sk.top() == "(" or precedence(r) > precedence(sk.top())) sk.push(r));
            else if (c == '(') sk.push(r);
            else if (c == ')') {
                while (sk.top() != "(") {
                    postfix += sk.top(); postfix.push_back(' '); sk.pop();
                }
                sk.pop();
            }
            else {
                while (!sk.empty() and precedence(sk.top()) >= precedence(r)) {
                    postfix += sk.top(); postfix.push_back(' '); sk.pop();
                }
                sk.push(r);
            }
        }
        ++c;
    }
    while (!sk.empty()) {
        postfix += sk.top(); postfix.push_back(' '); sk.pop();
    }
    cout << "The postfix notation is: " << postfix << endl;

//    stack<int> sk1; int i = 0;
//    while (i < postfix.size()) {
//        if (postfix[i] == ' ') {
//            ++i; continue;
//        }
//        string st;
//        while (postfix[i] >= '0' and postfix[i] <= '9') {
//            st.push_back(postfix[i]); ++i;
//        }
//        if (!st.empty()) sk1.push(stoint(st));
//        else {
//            int a = sk1.top(); sk1.pop(); int b = sk1.top(); sk1.pop();
//            int t = operation(a, b, postfix[i]); sk1.push(t); ++i;
////            cout << a << ' ' << b << ' ' << t << endl;
//        }
//    }
//    cout << "The result is: " << sk1.top() << endl;
    return 0;
}
