# Complexity: O(n*log(n))
# Use: Used to determine the number of unique substrings in a string using suffix array and lcp array of kasai algorithm.

def dsub(s):
    n = len(s)
    sfx = [{'index': i, 'rank': [ord(s[i]) - ord('a'), ord(s[i + 1]) - ord('a') if i + 1 < n else -1]} for i in range(n)]
    sfx.sort(key=lambda x: (x['rank'][0], x['rank'][1]))
    ind = [0] * n; k = 4
    while k < 2 * n:
        rnk, prev = 0, sfx[0]['rank'][0]
        sfx[0]['rank'][0] = rnk; ind[sfx[0]['index']] = 0
        for i in range(1, n):
            if sfx[i]['rank'] == [prev, sfx[i - 1]['rank'][1]]:
                sfx[i]['rank'][0] = rnk
            else:
                prev = sfx[i]['rank'][0]; rnk += 1; sfx[i]['rank'][0] = rnk
            ind[sfx[i]['index']] = i
        for i in range(n):
            next_index = sfx[i]['index'] + (k >> 1)
            sfx[i]['rank'][1] = sfx[ind[next_index]]['rank'][0] if next_index < n else -1
        sfx.sort(key=lambda x: (x['rank'][0], x['rank'][1])); k <<= 1
    suf = [x['index'] for x in sfx]; inv = [0] * n
    for i in range(n): inv[suf[i]] = i
    lcp = [0] * n; k = 0
    for i in range(n):
        if inv[i] == n - 1: k = 0; continue
        j = suf[inv[i] + 1]
        while i + k < n and j + k < n and s[i + k] == s[j + k]: k += 1
        lcp[inv[i]] = k; k = max(k - 1, 0)
    res = n - suf[0]
    for i in range(1, n): res += (n - suf[i]) - lcp[i - 1]
    return res