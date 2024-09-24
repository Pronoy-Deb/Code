# Complexity: O(|str| + |pat|)
# Application: Used to find all occurrences of a pattern in a text in linear time

def z(str, pat):
    s = pat + '$' + str; pl, tl = len(pat), len(s)
    Z = [0] * tl; l, r = 0, 0
    for i in range(1, tl):
        if i > r:
            l, r = i, i
            while r < tl and s[r - l] == s[r]: r += 1
            Z[i] = r - l; r -= 1
        else:
            k = i - l
            if Z[k] < r - i + 1: Z[i] = Z[k]
            else:
                l = i
                while r < tl and s[r - l] == s[r]: r += 1
                Z[i] = r - l; r -= 1
    ind = [i - pl - 1 for i in range(tl) if Z[i] == pl]
    return ind

# Example usage
text = "abcxabcdabxabcdabcdabcy"
pattern = "abcdabcy"
ind = z(text, pattern)
print("Pattern found at ind:", ind)

# Problem: lightoj.com/problem/substring-frequency