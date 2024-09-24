// Complexity: O(log(n))
// To check whether a character is vowel:

bool vow(char c) {
    set<char> st = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    return (st.find(c) != st.end());
}

// To check whether a character is consonant:

bool con(char c) {
    set<char> st = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    return (st.find(c) == st.end());
}