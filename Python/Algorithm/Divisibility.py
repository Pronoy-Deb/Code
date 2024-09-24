# Complexity: O(|s|)

def two(s): return int(s[-1]) % 2 == 0

def three(s): return sum(int(digit) for digit in s) % 3 == 0

def four(s): return int(s[-2:]) % 4 == 0

def five(s): return s[-1] in ['0', '5']

def six(s): return two(s) and three(s)

def eight(s): return int(s[-3:]) % 8 == 0

def nine(s): return sum(int(digit) for digit in s) % 9 == 0

def ten(s): return s[-1] == '0'

def eleven(s):
    alternates = sum(int(s[i]) if i % 2 == 0 else -int(s[i]) for i in range(len(s)))
    return alternates % 11 == 0

def twelve(s): return three(s) and four(s)

def fifteen(s): return three(s) and five(s)

def eighteen(s): return two(s) and nine(s)

def forty_five(s): return five(s) and nine(s)
