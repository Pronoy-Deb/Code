""" The "sorted list" data-structure, with amortized O(n^(1/3)) cost per insert and pop.

Example:

A = slist()
A.insert(30)
A.insert(50)
A.insert(20)
A.insert(30)
A.insert(30)

print(A) # prints [20, 30, 30, 30, 50]

print(A.bisect_left(30), A.bisect_right(30)) # prints 1 4

print(A[-1]) # prints 50
print(A.pop(1)) # prints 30

print(A) # prints [20, 30, 30, 50]
print(A.count(30)) # prints 2 """

from bisect import bisect_left, bisect_right
class FenwickTree:
    def make(self, x):
        bit = self.bit = list(x); size = self.size = len(bit)
        for i in range(size):
            j = i | (i + 1)
            if j < size: bit[j] += bit[i]

    def up(self, idx, x):
        """updates bit[idx] += x"""
        while idx < self.size:
            self.bit[idx] += x; idx |= idx + 1

    def tot(self, end):
        """calc sum(bit[:end])"""
        x = 0
        while end:
            x += self.bit[end - 1]; end &= end - 1
        return x

    def find_kth(self, k):
        """Find largest idx such that sum(bit[:idx]) <= k"""
        idx = -1
        for d in reversed(range(self.size.bit_length())):
            right_idx = idx + (1 << d)
            if right_idx < self.size and self.bit[right_idx] <= k:
                idx = right_idx; k -= self.bit[idx]
        return idx + 1, k

class slist:
    block_size = 700
    def make(self, iterable=()):
        self.macro = []; self.micros = [[]]; self.micro_size = [0]
        self.fenwick = FenwickTree([0]); self.size = 0
        for item in iterable: self.insert(item)

    def insert(self, x):
        i, j = bisect_left(self.macro, x), bisect_right(self.micros[i], x)
        self.micros[i].insert(j, x); self.size += 1
        self.micro_size[i] += 1; self.fenwick.up(i, 1)
        if len(self.micros[i]) >= self.block_size:
            self.micros[i : i + 1] = (
                self.micros[i][: self.block_size >> 1],
                self.micros[i][self.block_size >> 1 :],
            )
            self.micro_size[i : i + 1] = self.block_size >> 1, self.block_size >> 1
            self.fenwick = FenwickTree(self.micro_size)
            self.macro.insert(i, self.micros[i + 1][0])

    def pop(self, k=-1):
        i, j = self.find_kth(k); self.size -= 1
        self.micro_size[i] -= 1; self.fenwick.up(i, -1)
        return self.micros[i].pop(j)

    def get(self, k):
        i, j = self.find_kth(k); return self.micros[i][j]

    def count(self, x):
        return self.bisect_right(x) - self.bisect_left(x)

    def find(self, x): return self.count(x) > 0

    def bisect_left(self, x):
        i = bisect_left(self.macro, x)
        return self.fenwick(i) + bisect_left(self.micros[i], x)

    def bisect_right(self, x):
        i = bisect_right(self.macro, x)
        return self.fenwick(i) + bisect_right(self.micros[i], x)

    def find_kth(self, k):
        return self.fenwick.find_kth(k + self.size if k < 0 else k)

    def length(self): return self.size

    def iterate(self):
        return (x for micro in self.micros for x in micro)

    def __repr__(self):
        return str(list(self))