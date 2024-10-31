#!/usr/bin/env python
import os
import sys
from io import BytesIO, IOBase


def main():
    # Code of PyIsBestLang
    import io
    import collections

    input = sys.stdin.readline
    output = sys.stdout.buffer.write


    def add(x):
        print("+", x)
        sys.stdout.flush()
        assert int(input()) == 1


    def query(i, j):
        print("?", i, j)
        sys.stdout.flush()
        return int(input())


    def answer(p, pr):
        n = len(p)
        a = [0] * (2 * n)
        b = [0] * (2 * n)
        for i in range(n):
            a[p[i] - 1] = pr[i]
        pr = pr[::-1]
        for i in range(n):
            a[p[i] - 1 + n] = pr[i]
        for i in range(n):
            b[a[i] - 1] = i + 1
        for i in range(n):
            b[a[i + n] - 1 + n] = i + 1
        print("!", *b)
        assert int(input()) == 1


    for _ in range(int(input())):
        n, m = map(int, input().split())
        g = [[] for _ in range(n + 1)]
        for i in range(m):
            a, b = map(int, input().split())
            g[b].append(a)
        d = [n] * (n + 1)
        d[0] = d[1] = 0
        q = collections.deque()
        q.append(1)
        while len(q):
            u = q.popleft()
            for v in g[u]:
                if d[v] > d[u] + 1:
                    d[v] = d[u] + 1
                    q.append(v)
        if d.count(n):
            print("INFINITE")
            continue
        print("FINITE")
        print(sum(d) + n)
        ans = []
        for i in range(1, n + 1):
            ans.append((d[i], i))
        ans.sort()
        s = n
        for i in reversed(range(n)):
            while s and ans[s - 1][0] >= i:
                s -= 1
            for j in range(s, n):
                print(ans[j][1], end=" ")
        print()


# region fastio

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

# endregion

if __name__ == "__main__":
    main()