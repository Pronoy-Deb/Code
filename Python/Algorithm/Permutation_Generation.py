# Complexity: O(n!)
# Printing all permutations of a sorted sequence in ascending order:

from itertools import permutations
v = [1, 2, 3]
for perm in sorted(permutations(v)):
    print(' '.join(map(str, perm)))

# Printing all permutations of a sorted sequence in descending order:

from itertools import permutations
v = [3, 2, 1]
for perm in sorted(permutations(v), reverse=True):
    print(' '.join(map(str, perm)))

# Comparing whether permutation or not:

from collections import Counter
v = [5, 2, 4, 3, 1]
v1 = [4, 3, 2, 5, 1]
print(Counter(v) == Counter(v1))