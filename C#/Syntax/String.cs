// To determine the length of a string:
    int length = s.Length;

// To access the last character:
    char last = s[^1];

// To access the second last character:
    char secondLast = s[^2];

// To access a substring:
    string sub = s[1..4]; // from index 1 to 3
    string sub = s[1..]; // from index 1 to the end
    string sub = s[..4]; // from the start to index 3
    string sub = s[..]; // the whole string

// To access a substring in reverse:
    string sub = s[^4..^1]; // from the 4th last to the 2nd last
    string sub = s[^4..]; // from the 4th last to the end
    string sub = s[^1..]; // the last character

// Check if the character at index i is lowercase
    char.IsLower(s[i])

// Check if the character at index i is uppercase
    char.IsUpper(s[i])