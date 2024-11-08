from os import read, write, fstat; from sys import stdin, stdout, setrecursionlimit; from io import BytesIO, IOBase; setrecursionlimit(300000); BS = 8192
class FastIO(IOBase):
    nl = 0
    def __init__(self, file): self._file = file; self._fd = file.fileno(); self.buffer = BytesIO(); self.writable = "x" in file.mode or "r" not in file.mode; self.write = self.buffer.write if self.writable else None
    def read(self):
        while True:
            b = read(self._fd, max(fstat(self._fd).st_size, BS))
            if not b: break
            ptr = self.buffer.tell(); self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.nl = 0; return self.buffer.read()
    def readline(self):
        while not self.nl: b = read(self._fd, max(fstat(self._fd).st_size, BS)); self.nl = b.count(b"\n") + (not b); ptr = self.buffer.tell(); self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.nl -= 1; return self.buffer.readline()
    def flush(self):
        if self.writable: write(self._fd, self.buffer.getvalue()); self.buffer.truncate(0), self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file): self.buffer = FastIO(file); self.flush = self.buffer.flush; self.writable = self.buffer.writable; self.write = lambda s: self.buffer.write(s.encode("ascii")); self.read = lambda: self.buffer.read().decode("ascii"); self.readline = lambda: self.buffer.readline().decode("ascii")
stdin, stdout = IOWrapper(stdin), IOWrapper(stdout); input = lambda: stdin.readline().rstrip("\r\n")
def ck(*A): from inspect import currentframe as cf; from sys import stderr; frame = cf().f_back; name = {id(v): k for k, v in frame.f_locals.items()}; [print(f"{name.get(id(var), 'val')} = " + (f"[{', '.join(map(str, var))}]" if isinstance(var, list) else f"{{{', '.join(f'{k}: {v}' for k, v in var.items())}}}" if isinstance(var, dict) else f"{{{', '.join(map(str, var))}}}" if isinstance(var, set) else f"({', '.join(map(str, var))})" if isinstance(var, tuple) else str(var)), file=stderr) for var in A]
def ps(b): print("YES" if b else "NO")
M, N = int(1e9) + 7, int(5e4) + 5
par, sz = [0] * N, [0] * N
def make(n):
    for i in range(1, n + 1): par[i] = i; sz[i] = 1
def get(i):
    if par[i] == i: return i
    par[i] = get(par[i]); return par[i]
def uni(a, b):
    a = get(a); b = get(b)
    if a != b:
        if sz[a] < sz[b]: a, b = b, a
        par[b] = a; sz[a] += sz[b]
def same(a, b): return get(a) == get(b)
def size(a): return sz[get(a)]
def cnt(): return sum(get(i) == i for i in range(1, len(par)))
def test(tc):
    n, m, q = map(int, input().split())
    # ls = list(map(int, input().split()))
    for _ in range(m): u, v = map(int, input().split())
    ls = []
    for i in range(q):
        c, a, b = input().strip().split()
        ls.append(1 if c == "ask" else 0)
        ls.append(int(a)); ls.append(int(b))
    # global par, sz; par, sz = [0] * (n + 5), [0] * (n + 5)
    make(n); ans = []
    for i in range(len(ls) - 1, -1, -3):
        c, a, b = ls[i - 2], ls[i - 1], ls[i]
        if c: ans.append(same(a, b))
        else: uni(a, b)
    for i in range(len(ans) - 1, -1, -1): ps(ans[i])

if __name__ == "__main__":
    t = tc = 1
    # tc = int(input())
    while t <= tc: test(t); t += 1