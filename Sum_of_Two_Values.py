from os import read, write, fstat; from sys import stdin, stdout; from io import BytesIO, IOBase; BS = 8192
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
def ck(*args):
    import inspect; from sys import stderr; frame = inspect.currentframe().f_back; name = frame.f_locals
    for var in args: stderr.write(f"{([k for k, v in name.items() if v is var][0] if [k for k, v in name.items() if v is var] else 'val')} = " + (f"[{', '.join(map(str, var))}]" if isinstance(var, list) else f"{{{', '.join(f'{k}: {v}' for k, v in var.items())}}}" if isinstance(var, dict) else f"{{{', '.join(map(str, var))}}}" if isinstance(var, set) else f"({', '.join(map(str, var))})" if isinstance(var, tuple) else str(var)) + "\n")
ini = lambda: (c := stdin.readline().split(), int(c[0]) if len(c) == 1 else [int(x) for x in c])[1]
ins = lambda: (c := stdin.readline().split(), c[0] if len(c) == 1 else [x for x in c])[1]
def pn(c, n): [stdout.write(str(c[i]) + ' ') for i in range(n)]; stdout.write("\n")
def ps(b): stdout.write("YES\n" if b else "NO\n")
def pc(t): stdout.write("Case " + str(t) + ": ")
def out(*A): stdout.write(' '.join(map(str, A)) + "\n")
M, N = 1000000007, 200005

# from collections import OrderedDict

def test(tc):
    n, k = map(int, input().split())
    ls = list(map(int, input().split()))
    # dc = OrderedDict()
    dc = {}
    for i, val in enumerate(ls):
        if k - val in dc:
            out(dc[k - val] + 1, i + 1)
            return
        dc[val] = i
    out("IMPOSSIBLE")

if __name__ == "__main__":
    t = tc = 1
    # tc = ini()
    while t <= tc: test(t); t += 1