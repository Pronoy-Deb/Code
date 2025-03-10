// Space Remover for Codebook:

#include <bits/stdc++.h>
using namespace std;

bool op(string &s) {
    return (s == "*" || s == "+" || s == "-" || s == "/" || s == "^" || s == "&" || s == "|" || s == "==" || s == "=" || s == "!=" || s == ">" || s == "<" || s == "<=" || s == ">=" || s == "," || s == "?" || s == ":" || s == "{" || s == "}" || s == "(" || s == ")" || s == "[" || s == "]" || s == ">>" || s == "<<" || s == "&=" || s == "|=" || s == "^=" || s == "+=" || s == "-=" || s == "*=" || s == "-=" || s == "/=");
}

// Given a code it will congest the code but the code will remain compilable.
// You can use it when you want to save some space in your 25 pages codebook.
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    while (getline(cin, s))
    {
        string p = "";
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ' || s[i] == '\t')
            {
                continue;
            }
            else
            {
                for (int j = i; j < s.size(); j++)
                {
                    if (j + 1 < s.size() and s[j] == ',' and s[j + 1] == ' ')
                    {
                        p += s[j];
                        j++;
                    }
                    else if (j + 1 < s.size() and s[j] == ';' and s[j + 1] == ' ')
                    {
                        p += s[j];
                        j++;
                    }
                    else
                    {
                        p += s[j];
                    }
                }
                break;
            }
        }
        s = p;
        if (s.find("//") != -1 || s.find("include") != -1)
        {
            cout << s << '\n';
        }
        else
        {
            vector<string> v;
            string w;
            stringstream ss(s);
            while (ss >> w)
            {
                if (w == "||")
                    w = "||";
                if (w == "and")
                    w = "&&";
                v.push_back(w);
            }
            for (int i = 0; i < v.size(); i++)
            {
                if (i)
                {
                    if (op(v[i - 1]) || op(v[i]))
                        ;
                    else if (v[i - 1].back() == ')' || v[i].front() == '(')
                        ;
                    else
                        cout << ' ';
                }
                cout << v[i];
            }
        }
    }
    return 0;
}