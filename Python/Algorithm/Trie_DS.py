# To compute Maximum Xor Subarray:

class Triend:
    def __init__(self): self.cld = {}; self.value = None

def insert(root, pxor):
    nd = root
    for i in reversed(range(31)):  # Assume 32-bit integer
        bit = (pxor >> i) & 1
        if bit not in nd.cld: nd.cld[bit] = Triend()
        nd = nd.cld[bit]
    nd.value = pxor

def query(root, pxor):
    nd = root
    for i in reversed(range(31)):  # Assume 32-bit integer
        bit = (pxor >> i) & 1
        tbit = 1 - bit
        if tbit in nd.cld: nd = nd.cld[tbit]
        else: nd = nd.cld.get(bit, nd)
    return pxor ^ nd.value

def mxor(arr):
    root = Triend(); pxor = 0
    insert(root, pxor); res = float('-inf')
    for num in arr:
        pxor ^= num; insert(root, pxor)
        res = max(res, query(root, pxor))
    return res

# Example usage
arr = [8, 1, 2, 12]
print("Maximum XOR Subarray value is:", mxor(arr))

# OR,

class TrieNode:
    def __init__(self):
        self.childNode = [None] * 26
        self.wordCount = 0

def insert_key(root, key):
    currentNode = root

    for c in key:
        if not currentNode.childNode[ord(c) - ord('a')]:
            newNode = TrieNode()
            currentNode.childNode[ord(c) - ord('a')] = newNode
        currentNode = currentNode.childNode[ord(c) - ord('a')]
    currentNode.wordCount += 1

def search_key(root, key):
    currentNode = root

    for c in key:
        if not currentNode.childNode[ord(c) - ord('a')]: return False
        currentNode = currentNode.childNode[ord(c) - ord('a')]

    return currentNode.wordCount > 0

def delete_key(root, word):
    currentNode, lastBranchNode, lastBrachChar = root, None, 'a'

    for c in word:
        if not currentNode.childNode[ord(c) - ord('a')]: return False
        else:
            count = 0
            for i in range(26):
                if currentNode.childNode[i]: count += 1
            if count > 1:
                lastBranchNode = currentNode
                lastBrachChar = c
            currentNode = currentNode.childNode[ord(c) - ord('a')]

    count = 0
    for i in range(26):
        if currentNode.childNode[i]:
            count += 1

    if count > 0:
        currentNode.wordCount -= 1
        return True

    if lastBranchNode:
        lastBranchNode.childNode[ord(lastBrachChar) - ord('a')] = None
        return True
    else:
        root.childNode[ord(word[0]) - ord('a')] = None
        return True
if __name__ == '__main__':
    root = TrieNode()

    input_strings = ["and", "ant", "do", "geek", "dad", "ball"]

    n = len(input_strings)

    for i in range(n):
        insert_key(root, input_strings[i])

    search_query_strings = ["do", "geek", "bat"]

    search_queries = len(search_query_strings)

    for i in range(search_queries):
        print("Query String:", search_query_strings[i])
        if search_key(root, search_query_strings[i]):
            print("The query string is present in the Trie")
        else:
            print("The query string is not present in the Trie")

    delete_query_strings = ["geek", "tea"]
    delete_queries = len(delete_query_strings)

    for i in range(delete_queries):
        print("Query String:", delete_query_strings[i])
        if delete_key(root, delete_query_strings[i]):
            print("The query string is successfully deleted")
        else:
            print("The query string is not present in the Trie")

