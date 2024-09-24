import os, sys, random, time; from io import BytesIO, IOBase; BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0
    def __init__(self, file): self._file = file; self._fd = file.fileno(); self.buffer = BytesIO(); self.writable = "x" in file.mode or "r" not in file.mode; self.write = self.buffer.write if self.writable else None
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b: break
            ptr = self.buffer.tell(); self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0; return self.buffer.read()
    def readline(self):
        while not self.newlines: b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE)); self.newlines = b.count(b"\n") + (not b); ptr = self.buffer.tell(); self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1; return self.buffer.readline()
    def flush(self):
        if self.writable: os.write(self._fd, self.buffer.getvalue()); self.buffer.truncate(0), self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file): self.buffer = FastIO(file); self.flush = self.buffer.flush; self.writable = self.buffer.writable; self.write = lambda s: self.buffer.write(s.encode("ascii")); self.read = lambda: self.buffer.read().decode("ascii"); self.readline = lambda: self.buffer.readline().decode("ascii")
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout); input = lambda: sys.stdin.readline().rstrip("\r\n")
def pn(c, n): [print(c[i], end = ' ') for i in range(n)]; print()
def ran(l, r): return l + random.randint(0, r - l)
def ps(b): return "YES" if b else "NO"
M = 1000000007; N = 200005
a, b, c, d, m, n = 0, 0, 0, 0, 0, 0; ls = []; ls1 = []; ls2 = []; s = ""

def optimized():

    return 

def bruteForce():

    return

def Test():
    for tc in range(10):
        n = ran(1, 5)
        # ls = list(map(int, input().split()))
        o = optimized()
        b = bruteForce()
        if b != o:
            print("Input:")
            print(n)
            # pn(ls2, n)
            print("Expected:")
            print(b)
            # pe(b)
            print("Found:")
            print(o)
            # pe(o)
            return
    print("Pretests Passed!")

if __name__ == "__main__":
    random.seed(time.time()); Test()