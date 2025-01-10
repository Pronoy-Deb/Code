// To determine the length of a string:
    int length = s.Length;

// To access the last character:
    char last = s[^1];

// To access a substring:
    string sub = s[1..4]; // from index 1 to 3
    string sub = s[1..]; // from index 1 to the end
    string sub = s[..4]; // from the start to index 3
    string sub = s[..]; // the whole string