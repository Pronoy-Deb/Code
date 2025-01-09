#include <bits/stdc++.h>
using namespace std;

char rel(string &s, string &r) {
    if (s == "id" && r == "id") return '-';
    if (s == "$" && r == "$") return 'A';
    if (s == "id" || r == "$") return '>';
    if (s == "$" || r == "id") return '<';
    if (s == "+") {
        if (r == "*" || r == "^") return '<';
        return '>';
    }
    if (s == "*") {
        if (r == "+" || r == "^") return '>';
        return '<';
    }
    if (s == "^") {
        if (r == "+" || r == "*") return '>';
        return '<';
    }
}

int main() {
    map<string, string> grammar;
    grammar["E + E"] = grammar["E * E"] = grammar["E ^ E"] = grammar["id"] = "E";
    cout << "Enter the production: ";
    string s; getline(cin, s);
    vector<string> w; string r;
    for (char c : s) {
        if (c == ' ') w.push_back(r), r.clear();
        else r += c;
    }
    if (!r.empty()) w.push_back(r); w.push_back("$");
    int i = 0; string ip = w[i];
    stack<string> sk, terminal; sk.push("$");
    while (true) {
        if (sk.top() == "$" && ip == "$" && terminal.size() == 1 && terminal.top() == grammar.begin()->second) {
            cout << "Accepted!\n"; break;
        }
        string a = sk.top(), b = ip;
        char relation = rel(a, b);
        if (relation == '<') {
            sk.push(b); ip = w[++i];
            cout << "Shift Operation Performed!\n";
        }
        else if (relation == '>') {
            do {
                string recent = sk.top(); sk.pop();
                if (recent != w[0]) {
                    string st = terminal.top();
                    terminal.pop();
                    st += " " + recent + " " + terminal.top();
                    terminal.pop();
                    terminal.push(grammar[st]);
                }
                else terminal.push(grammar[w[0]]);
                cout << "Reduce Operation Performed!\n";
            } while (rel(sk.top(), ip) == '>');
        }
    }
    return 0;
}