// Returns: true / false
// Changes the behaviour of the built-in sort() function
// Calling: sort(v.begin(), v.end(), cmp);

// Sorts a vector of pair in ASCENDING order according to the second element:
bool cmp(const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
    return (a.second < b.second);
}

// Sorts a set / multiset of pair in ASCENDING order according to the second element:
struct cmp {
    bool operator() (const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) const {
        return a.second < b.second;
    }
};

// Sorts a vector of pair in DESCENDING order according to the second element:
bool cmp(const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
    return (a.second > b.second);
}

// Sorts a vector of string in ASCENDING order according to the size():
bool cmp(const string &a, const string &b) {
    return (a.size() < b.size());
}

// Sorts a vector of string in DESCENDING order according to the size():
bool cmp(const string &a, const string &b) {
    return (a.size() > b.size());
}

// Sorts a vector of pair in ASCENDING order according to the sum of the pair:
bool cmp(const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
    return (a.first + a.second) < (b.first + b.second);
}

// Sorts Ascending pair of first elements & Descending pair of second elements
bool cmp(const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
    if(a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}