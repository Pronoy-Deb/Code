// Returns: true / false
// Work: Changes the behaviour of the built-in sort() function
// Calling: sort(v.begin(), v.end(), cmp);

// Work: Prints Ascending pair of first elements & Descending pair of second elements
auto cmp(const pair<long long, long long> &a, const pair<long long, long long> &b) {
    if(a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}

// Work: Sorts a vector of pair in ASCENDING order according to the second element:
auto cmp(const pair<long long, long long> &a, const pair<long long, long long> &b) {
    return (a.second < b.second);
}

// Work: Sorts a vector of pair in DESCENDING order according to the second element:
auto cmp(const pair<long long, long long> &a, const pair<long long, long long> &b) {
    return (a.second > b.second);
}

// Work: Sorts a vector of string in ASCENDING order according to the size():
auto cmp(const string &a, const string &b) {
    return (a.size() < b.size());
}

// Work: Sorts a vector of string in DESCENDING order according to the size():
auto cmp(const string &a, const string &b) {
    return (a.size() > b.size());
}

// Work: Sorts a vector of pair in ASCENDING order according to the sum of the pair:
auto cmp(const pair<long long, long long> &a, const pair<long long, long long> &b) {
    return (a.first + a.second) < (b.first + b.second);
}