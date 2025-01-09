#include<bits/stdc++.h>
using namespace std;

int precedence(string &c) {
    if (c == "^") return 4;
    if (c == "/" or c == "*") return 3;
    if (c == "+" or c == "-") return 2;
    return 1;
}
int operation(int b, int a, char c) {
    if (c == '+') return a + b;
    if (c == '-') return a - b;
    if (c == '*') return a * b;
    if (c == '/') return a / b;
    return pow(a, b);
}
int stoint(string &s) {
    int n = 0;
    for (int i = s[0] == '-'; i < s.size(); ++i) {
        n = n * 10 + (s[i] - '0');
    }
    return n * (s[0] == '-' ? -1 : 1);
}
int main() {
    cout << "Enter the space separated expression: ";
    string s; getline(cin, s);
    string postfix;
    stack<string> sk; int c = 0;
    while (c < s.size()) {
        while (s[c] == ' ') ++c;
        string st; while (isalnum(s[c])) st += s[c++];
        if (!st.empty()) postfix += st + ' ';
        else {
            string r = string(1, s[c]);
            if (r == "-" and isalnum(s[c + 1])) {
                st = "-"; while (isalnum(s[++c])) st += s[c];
                postfix += st + ' '; continue;
            }
            if (r == "(") sk.push(r);
            else if (r == ")") {
                while (sk.top() != "(") {
                    postfix += sk.top() + ' '; sk.pop();
                }
                sk.pop();
            }
            else {
                while (!sk.empty() and precedence(sk.top()) >= precedence(r)) {
                    postfix += sk.top() + ' '; sk.pop();
                }
                sk.push(r);
            }
            ++c;
        }
    }
    while (!sk.empty()) {
        postfix += sk.top() + ' '; sk.pop();
    }
    postfix.pop_back();
    cout << "The postfix notation is: " << postfix << endl;

    stack<int> sk1; int i = 0, j = 1; map<string, int> mp;
    while (i < postfix.size()) {
        while (postfix[i] == ' ') ++i;
        string st;
        if (postfix[i] == '-' and isdigit(postfix[i + 1])) {
            st = "-"; while (isdigit(postfix[++i])) st += postfix[i];
        }
        while (isdigit(postfix[i])) st += postfix[i++];
        if (!st.empty()) sk1.push(stoint(st));
        else {
            int a = sk1.top(); sk1.pop(); int b = sk1.top(); sk1.pop();
            int t = operation(a, b, postfix[i]); sk1.push(t); ++i;
            st = "t" + to_string(j++); mp[st] = t;
            // cout << a << ' ' << b << ' ' << t << endl;
        }
    }
    // for (auto &i : mp) cout << i.first << ": " << i.second << endl;
    cout << "The result is: " << sk1.top() << endl;
    return 0;
}

// 2 + 3 + 4   (2 * -6 / -3) - (3 * -1)