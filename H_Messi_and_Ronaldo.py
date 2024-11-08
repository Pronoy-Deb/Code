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
def ck(*A): from inspect import currentframe as cf; from sys import stderr; frame = cf().f_back; name = {id(v): k for k, v in frame.f_locals.items()}; [print(f"{name.get(id(var), 'val')} = " + (f"[{', '.join(map(str, var))}]" if isinstance(var, list) else f"{{{', '.join(f'{k}: {v}' for k, v in var.items())}}}" if isinstance(var, dict) else f"{{{', '.join(map(str, var))}}}" if isinstance(var, set) else f"({', '.join(map(str, var))})" if isinstance(var, tuple) else str(var)), file=stderr) for var in A]
def ps(b): print("YES" if b else "NO")
M, N = int(1e9) + 7, int(2e5) + 5

# class Stack:
#     def __init__(self): self._items = []
#     def push(self, item): self._items.append(item)
#     def pop(self):
#         if not self.isEmpty(): return self._items.pop()
#         raise IndexError("Underflow!")
#     def isEmpty(self): return len(self._items) == 0

# class _BSTNode(object):
#     def __init__(self, key, value):
#         self.key = key; self.value = value
#         self.left = self.right = None
#     def __str__(self):
#         return str(self.key) + ": " + str(self.value)

# class sdict(object):
#     def __init__(self):
#         self._root = None; self._size = 0
#     def __len__(self): return self._size
#     def __contains__(self, key): return not self._findNode(self._root, key) is None
#     def __getitem__(self, key):
#         node = self._findNode(self._root, key)
#         if node == None: raise KeyError()
#         return node.value
#     def get(self, key):
#         node = self._findNode(self._root, key)
#         if node == None: return None
#         else: return node.value
#     def _findNode(self, subtree, key):
#         if subtree == None: return None
#         elif subtree.key == key: return subtree
#         elif subtree.key < key: return self._findNode(subtree.right, key)
#         else: return self._findNode(subtree.left, key)
#     def __setitem__(self, key, value):
#         if self._root == None:
#             self._root = _BSTNode(key, value); self._size += 1
#         else: self._setItem(self._root, key, value)
#     def _setItem(self, subtree, key, value):
#         assert subtree is not None
#         if subtree.key == key: subtree.value = value
#         elif key < subtree.key:
#             if subtree.left is None:
#                 subtree.left = _BSTNode(key, value); self._size += 1
#             else: self._setItem(subtree.left, key, value)
#         else:
#             if subtree.right is None:
#                 subtree.right = _BSTNode(key, value); self._size += 1
#             else: self._setItem(subtree.right, key, value)
#     def __str__(self):
#         result = "{"
#         for key in self: result += str(key) + ": " + str(self[key]) + ", "
#         result = result.rstrip(", ")
#         return result + "}"
#     def __iter__(self): return _InorderBSTIterator(self._root)
#     def _height(self, subtree):
#         if subtree is None: return 0
#         else: return 1 + max(self._height(subtree.left), self._height(subtree.right))
#     def pop(self, key):
#         value = self[key]
#         self._root = self._bstRemove(self._root, key)
#         self._size -= 1; return value
#     def _bstRemove(self, subtree, key):
#         assert subtree is not None, "Cannot remove non-existent key."
#         if key < subtree.key:
#             subtree.left = self._bstRemove(subtree.left, key); return subtree
#         elif key > subtree.key:
#             subtree.right = self._bstRemove(subtree.right, key); return subtree
#         else:
#             if subtree.left is None and subtree.right is None: return None
#             elif subtree.left is not None and subtree.right is None: return subtree.left
#             elif subtree.left is None and subtree.right is not None: return subtree.right
#             else:
#                 successor = self._bstMinimum(subtree.right)
#                 subtree.key = successor.key; subtree.value = successor.value
#                 subtree.right = self._bstRemove(subtree.right, successor.key)
#                 return subtree
#     def _bstMinimum(self, subtree):
#         if subtree is None: return None
#         if subtree.left is None: return subtree
#         else: return self._bstMinimum(subtree.left)

# class _InorderBSTIterator(object):
#     def __init__(self, root):
#         self.stack = Stack(); curNode = root
#         while curNode is not None:
#             self.stack.push(curNode); curNode = curNode.left
#     def __iter__(self): return self
#     def __next__(self):
#         if self.stack.isEmpty(): raise StopIteration()
#         curNode = self.stack.pop(); key = curNode.key
#         if curNode.right is not None:
#             self.stack.push(curNode.right); curNode = curNode.right.left
#             while curNode is not None:
#                 self.stack.push(curNode); curNode = curNode.left
#         return key

# from types import GeneratorType
# def bootstrap(f, stack=[]):
#     def wrappedfunc(*args, **kwargs):
#         if stack: return f(*args, **kwargs)
#         else:
#             to = f(*args, **kwargs)
#             while True:
#                 if type(to) is GeneratorType:
#                     stack.append(to); to = next(to)
#                 else:
#                     if stack: stack.pop()
#                     if not stack: break
#                     to = stack[-1].send(to)
#             return to
#     return wrappedfunc
# @bootstrap

def rec(n):
    if n == 1: return 0
    if dp.get(n) != None: return dp[n]
    a = rec(n >> 1)
    b = rec((n >> 1) + (n %2))
    dp[n] = n + a + b
    return dp[n]

def test(tc):
    n = int(input())
    global dp; dp = {}
    # ls = list(map(int, input().split()))
    print(rec(n))

if __name__ == "__main__":
    t = tc = 1
    # tc = int(input())
    while t <= tc: test(t); t += 1