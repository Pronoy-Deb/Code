# Returns: true/false
# Work: Changes the behaviour of the built-in sort() function

def cmp(item):
    return (item[0], -item[1])
pairs = [(1, 2), (1, 3), (2, 1)]

# Work: Prints Ascending pair of first elements & Descending pair of second elements

sorted_pairs = sorted(pairs, key = cmp)

# Work: Sorts a vector of pair in ASCENDING order according to the second element:

sorted_pairs = sorted(pairs, key=lambda x: x[1])

# Work: Sorts a vector of pair in DESCENDING order according to the second element:

sorted_pairs = sorted(pairs, key=lambda x: x[1], reverse=True)

# Work: Sorts a vector of string in ASCENDING order according to the size():

strings = ["abc", "a", "abcd"]
sorted_strings = sorted(strings, key=lambda x: len(x))

# Work: Sorts a vector of string in DESCENDING order according to the size():

sorted_strings = sorted(strings, key=lambda x: len(x), reverse=True)