# Complexity: O(|s|)
# -> base = 29: Immediate prime number after 26

# Cumulative Forward Hashing:

M = int(1e15 + 37)
def fhs(s, base = 29):
    n = len(s); pre = [0] * (n + 1); p = 1
    for i in range(n):
        pre[i + 1] = (pre[i] + (ord(s[i]) - ord('a') + 1) * p) % M
        p = (p * base) % M
    return pre

# Cumulative Backward Hashing:

def bhs(s, base = 29):
    sz = len(s); tmp = ord(s[-1]) - ord('a') + 1; p = base
    for i in range(sz - 2, -1, -1):
        tmp = ((tmp * base) + (ord(s[i]) - ord('a') + 1)) % M
        p = (p * base) % M
    return tmp

# Operation:
n = int(input()); s = str(input())
pre = fhs(s); st = set()
for i in range(n):
    hash_val = ((pre[i] * pow(base, length_skipped, M)) % M + (pre[n] - pre[i + length_skipped] + M)) % M
    st.add(hash_val)

# String Double Hashing:

def fhs(s, base):
    n = len(s); pre = [0] * (n + 1); p = 1
    for i in range(n):
        pre[i + 1] = (pre[i] + (ord(s[i]) - ord('a') + 1) * p) % M
        p = (p * base) % M
    return pre

def compute(s):
    pre29 = fhs(s, 29, M); pre31 = fhs(s, 31, M)
    return pre29, pre31

# Operation:
n = int(input()); s = str(input()); n = len(s)
pre29 = fhs(s, 29); pre31 = fhs(s, 31); st = set()
for i in range(length_skipped, n + 1):
    hash1 = (pre29[i - length_skipped] + ((pre29[n] - pre29[i] + M) * 853745547) % M) % M
    hash2 = (pre31[i - length_skipped] + ((pre31[n] - pre31[i] + M) * 746097820) % M) % M
    st.add((hash1, hash2))

# Problems:
#     https://codeforces.com/contest/1800/problem/D
#     https://codeforces.com/contest/271/problem/D