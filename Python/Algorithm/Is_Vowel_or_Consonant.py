# Complexity: O(1)

# To check whether a character is vowel:

def vow(c):
    vowels = "aeiouAEIOU"
    return c in vowels

# To check whether a character is consonant:

def con(c):
    vowels = "aeiouAEIOU"
    return c not in vowels and c.isalpha()