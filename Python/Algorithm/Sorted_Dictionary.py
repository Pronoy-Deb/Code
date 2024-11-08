# Works as like as CPP map
https://w3.cs.jmu.edu/spragunr/CS240_F12/lectures/maps/bst_map.py

class Stack:
    def __init__(self): self._items = []
    def push(self, item): self._items.append(item)
    def pop(self):
        if not self.isEmpty(): return self._items.pop()
        raise IndexError("Underflow!")
    def isEmpty(self): return len(self._items) == 0

class _BSTNode(object):
    def __init__(self, key, value):
        self.key = key; self.value = value
        self.left = self.right = None
    def __str__(self):
        return str(self.key) + ": " + str(self.value)

class sdict(object):
    def __init__(self):
        self._root = None; self._size = 0
    def __len__(self): return self._size
    def __contains__(self, key): return not self._findNode(self._root, key) is None
    def __getitem__(self, key):
        node = self._findNode(self._root, key)
        if node == None: raise KeyError()
        return node.value
    def get(self, key):
        node = self._findNode(self._root, key)
        if node == None: return None
        else: return node.value
    def _findNode(self, subtree, key):
        if subtree == None: return None
        elif subtree.key == key: return subtree
        elif subtree.key < key: return self._findNode(subtree.right, key)
        else: return self._findNode(subtree.left, key)
    def __setitem__(self, key, value):
        if self._root == None:
            self._root = _BSTNode(key, value); self._size += 1
        else: self._setItem(self._root, key, value)
    def _setItem(self, subtree, key, value):
        assert subtree is not None
        if subtree.key == key: subtree.value = value
        elif key < subtree.key:
            if subtree.left is None:
                subtree.left = _BSTNode(key, value); self._size += 1
            else: self._setItem(subtree.left, key, value)
        else:
            if subtree.right is None:
                subtree.right = _BSTNode(key, value); self._size += 1
            else: self._setItem(subtree.right, key, value)
    def __str__(self):
        result = "{"
        for key in self: result += str(key) + ": " + str(self[key]) + ", "
        result = result.rstrip(", ")
        return result + "}"
    def __iter__(self): return _InorderBSTIterator(self._root)
    def _height(self, subtree):
        if subtree is None: return 0
        else: return 1 + max(self._height(subtree.left), self._height(subtree.right))
    def pop(self, key):
        value = self[key]
        self._root = self._bstRemove(self._root, key)
        self._size -= 1; return value
    def _bstRemove(self, subtree, key):
        assert subtree is not None, "Cannot remove non-existent key."
        if key < subtree.key:
            subtree.left = self._bstRemove(subtree.left, key); return subtree
        elif key > subtree.key:
            subtree.right = self._bstRemove(subtree.right, key); return subtree
        else:
            if subtree.left is None and subtree.right is None: return None
            elif subtree.left is not None and subtree.right is None: return subtree.left
            elif subtree.left is None and subtree.right is not None: return subtree.right
            else:
                successor = self._bstMinimum(subtree.right)
                subtree.key = successor.key; subtree.value = successor.value
                subtree.right = self._bstRemove(subtree.right, successor.key)
                return subtree
    def _bstMinimum(self, subtree):
        if subtree is None: return None
        if subtree.left is None: return subtree
        else: return self._bstMinimum(subtree.left)

class _InorderBSTIterator(object):
    def __init__(self, root):
        self.stack = Stack(); curNode = root
        while curNode is not None:
            self.stack.push(curNode); curNode = curNode.left
    def __iter__(self): return self
    def __next__(self):
        if self.stack.isEmpty(): raise StopIteration()
        curNode = self.stack.pop(); key = curNode.key
        if curNode.right is not None:
            self.stack.push(curNode.right); curNode = curNode.right.left
            while curNode is not None:
                self.stack.push(curNode); curNode = curNode.left
        return key
