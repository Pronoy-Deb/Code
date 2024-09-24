# Complexity: O(n * w)

def rec(in_idx, wet, wt, val, dp):
    if wet == 0 or in_idx < 0: return 0
    if (in_idx, wet) in dp: return dp[(in_idx, wet)]
    ans = rec(in_idx - 1, wet, wt, val, dp)
    if wet - wt[in_idx] >= 0:
        ans = max(ans, rec(in_idx - 1, wet - wt[in_idx], wt, val, dp) + val[in_idx])
    dp[(in_idx, wet)] = ans
    return ans

def knap(n, w, wt, val):
    dp = {}; return rec(n-1, w, wt, val, dp)

# Example usage
n, w = map(int, input().split())
wt = []; val = []
for i in range(n):
    w_i, v_i = map(int, input().split())
    wt.append(w_i); val.append(v_i)
print(knap(n, w, wt, val))