# Addition:
# Complexity: O(max(|s|, |s1|));

def add(s, s1):
    sz, sz1 = len(s) - 1, len(s1) - 1; r, car = '', 0
    while sz >= 0 or sz1 >= 0:
        tmp = (int(s[sz]) if sz >= 0 else 0) + (int(s1[sz1]) if sz1 >= 0 else 0) + car
        car, tmp = divmod(tmp, 10)
        r += str(tmp); sz, sz1 = sz - 1, sz1 - 1
    if car: r += str(car)
    return r[::-1]

# Subtraction:
# Complexity: O(|s| + |s1|);

def sub(s, s1):
    sz, sz1 = len(s) - 1, len(s1) - 1; ck, car = False, 0
    if len(s) < len(s1) or (len(s) == len(s1) and s < s1):
        s, s1 = s1, s; sz, sz1 = sz1, sz; ck = True
    r = ''
    for i in range(sz, -1, -1):
        j = i - (sz - sz1)
        sub = (int(s[i]) - car) - (int(s1[j]) if j >= 0 else 0)
        if sub < 0: sub += 10; car = 1
        else: car = 0
        r += str(sub)
    r = r.rstrip('0') or '0'
    if ck: r += '-'
    return r[::-1]

# Multiplication:
# Complexity: O(|s| * |s1|)

def mul(s, s1):
    if s == "0" or s1 == "0": return "0"
    sz, sz1 = len(s), len(s1); res = [0] * (sz + sz1)
    for i in range(sz - 1, -1, -1):
        for j in range(sz1 - 1, -1, -1):
            mul = (ord(s[i]) - 48) * (ord(s1[j]) - 48)
            sum = mul + res[i + j + 1]
            res[i + j + 1] = sum % 10; res[i + j] += sum // 10
    pro = ''.join(map(str, res)).lstrip('0')
    return pro or "0"

# Division:
# Complexity: O(n^2)

def div(num, divi):
    idx, temp = 0, int(num[idx])
    while temp < divi:
        idx += 1
        if idx < len(num): temp = temp * 10 + int(num[idx])
        else: break
    ans = ''
    while len(num) > idx:
        ans += str(temp // divi)
        temp = (temp % divi) * 10 + int(num[idx]) if idx + 1 < len(num) else 0
        idx += 1
    return ans if ans else "0"