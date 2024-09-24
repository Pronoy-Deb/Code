# Complexity: O(|s|)

# Iterative Approach:
# Work: Works for all types of strings / brackets

def bal(s):
    o1, o2, o3 = 0, 0, 0
    for i in s:
        if o1 < 0 or o2 < 0 or o3 < 0:
            return False
        if i == '(': o1 += 1
        elif i == '{': o2 += 1
        elif i == '[': o3 += 1
        elif i == ')': o1 -= 1
        elif i == '}': o2 -= 1
        elif i == ']': o3 -= 1
    return o1 == 0 and o2 == 0 and o3 == 0


# Stack Approach:
# Work: Works only for "{[()]}" this type of a string, not "{[()}]" this

def bal_sk(s):
    mp = {'(': -1, '{': -2, '[': -3, ')': 1, '}': 2, ']': 3}
    sk = []
    for i in s:
        if mp.get(i, 0) < 0:
            sk.append(i)
        else:
            if not sk or mp[sk.pop()] + mp[i] != 0:
                return False
    return not sk