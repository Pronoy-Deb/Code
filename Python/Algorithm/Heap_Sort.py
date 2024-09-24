# Complexity: O(n*log(n))

def heapify(n, i):
    largest = i; l = (i << 1) + 1; r = (i << 1) + 2
    if l < n and ar[l] > ar[largest]: largest = l
    if r < n and ar[r] > ar[largest]: largest = r
    if largest != i:
        ar[i], ar[largest] = ar[largest], ar[i]
        heapify(n, largest)

def hsrt():
    n = len(ar)
    for i in range(n//2 - 1, -1, -1): heapify(n, i)
    for i in range(n-1, 0, -1):
        ar[i], ar[0] = ar[0], ar[i]
        heapify(i, 0)

# Example usage
ar = [12, 11, 13, 5, 6, 7]
hsrt()
print("Sorted array is:", ar)