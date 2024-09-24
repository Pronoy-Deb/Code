# Complexity: O(|p| + |s|)
# Application: Used to find all occurrences of a pattern in a text in linear time

def pre(pat):
    pl = len(pat); pi = [-1] * pl; now = -1
    for i in range(1, pl):
        while now != -1 and pat[now + 1] != pat[i]: now = pi[now]
        if pat[now + 1] == pat[i]: now += 1
        pi[i] = now
    return pi

def kmp(str, pat):
    pi = pre(pat); ans = 0; ind = []
    sl = len(str); pl = len(pat); now = -1
    for i in range(sl):
        while now != -1 and pat[now + 1] != str[i]: now = pi[now]
        if pat[now + 1] == str[i]: now += 1
        if now == pl - 1:
            ans += 1; ind.append(i - pl + 1); now = pi[now]
    return ans, ind

# Example usage
str = "ababcabcabababd"
pat = "ababd"
ans, ind = kmp(str, pat)
print(f"Pattern found {ans} times at ind: {ind}")

# Problem: lightoj.com/problem/substring-frequency