# WITHOUT lz Propagation:
# Complexity: Constructing the tree: O(n), Update & sum: O(log(n))

def make():
    tre = [0] * (2 * n)
    for i in range(n): tre[n + i] = ls[i]
    for i in range(n - 1, 0, -1):
        tre[i] = tre[(i << 1)] + tre[(i << 1) + 1]

def up(idx, val):
    idx += n; tre[idx] = val
    while idx > 1:
        tre[idx >> 1] = tre[idx] + tre[idx ^ 1]; idx >>= 1

def sum(l, r):
    res = 0; l += n; r += n
    while l < r:
        if l & 1:
            res += tre[l]; l += 1
        if r & 1:
            r -= 1; res += tre[r]
        l >>= 1; r >>= 1
    return res

# Operation:
global ls, tre, n
ls = list(map, int(input().split()))
make()
up(index, value)
sum(starting_index, ending_index + 1)

# WITH lz Propagation:
# Complexity: O(n)


def build(ls, tre, ss, se, si):
    if ss == se: tre[si] = ls[ss]; return
    mid = (ss + se) >> 1
    build(ls, tre, ss, mid, (si << 1) + 1)
    build(ls, tre, mid + 1, se, (si << 1) + 2)
    tre[si] = tre[(si << 1) + 1] + tre[(si << 1) + 2]

def make():
    tre = [0] * (4 * n); lz = [0] * (4 * n)
    build(ls, tre, 0, n - 1, 0)

def up(us, ue, dif, ss=0, se = None, si = 0):
    if se is None: se = n - 1
    if lz[si] != 0:
        tre[si] += (se - ss + 1) * lz[si]
        if ss != se:
            lz[(si << 1) + 1] += lz[si]; lz[(si << 1) + 2] += lz[si]
        lz[si] = 0
    if ss > se or ss > ue or se < us: return
    if ss >= us and se <= ue:
        tre[si] += (se - ss + 1) * dif
        if ss != se:
            lz[(si << 1) + 1] += dif; lz[(si << 1) + 2] += dif
        return
    mid = (ss + se) >> 1
    up(us, ue, dif, ss, mid, (si << 1) + 1)
    up(us, ue, dif, mid + 1, se, (si << 1) + 2)
    tre[si] = tre[(si << 1) + 1] + tre[(si << 1) + 2]

def sum(qs, qe, ss=0, se=None, si=0):
    if se is None: se = n - 1
    if lz[si] != 0:
        tre[si] += (se - ss + 1) * lz[si]
        if ss != se:
            lz[(si << 1) + 1] += lz[si]; lz[(si << 1) + 2] += lz[si]
        lz[si] = 0
    if ss > se or ss > qe or se < qs: return 0
    if ss >= qs and se <= qe: return tre[si]
    mid = (ss + se) >> 1
    return sum(qs, qe, ss, mid, (si << 1) + 1) + sum(qs, qe, mid + 1, se, (si << 1) + 2)

# Operation:
global ls, tre, lz, n
make();
up(starting_index, ending_index, value_to_add);
sum(starting_index, ending_index);