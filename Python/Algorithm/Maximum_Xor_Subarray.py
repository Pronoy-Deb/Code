# Complexity: O(n)
# Application: Used to determine the maximum xor sublsay using trie.

class TrieNode:
    def __init__(self): self.children = {}

def insert(root, x):
    node = root
    for i in range(30, -1, -1):
        y = (x >> i) & 1
        if y not in node.children: node.children[y] = TrieNode()
        node = node.children[y]

def search(root, x):
    node, ans = root, 0
    for i in range(30, -1, -1):
        y = (x >> i) & 1
        if y ^ 1 in node.children:
            node = node.children[y ^ 1]; ans += (1 << i)
        else: node = node.children.get(y, node)
    return ans

def xor(ls):
    root = TrieNode(); xr, mx = 0, 0; insert(root, xr)
    for x in ls:
        xr ^= x; insert(root, xr)
        mx = max(mx, search(root, xr))
    return mx