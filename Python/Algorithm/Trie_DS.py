# To compute Maximum Xor Subarray:

class Triend:
    def __init__(self):
        self.cld = {}; self.value = None

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