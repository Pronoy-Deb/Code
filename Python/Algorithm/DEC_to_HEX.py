# Complexity: O(n)
# ASCII: 48 = '0', 55 = 'A', 97 = 'a'

def hex(n):
    if n == 0: return "0"
    s = ""
    while n:
        tmp = n % 16
        if tmp < 10: s += chr(tmp + 48)  # Adding 48 to convert digit to ASCII
        else: s += chr(tmp + 55)  # Adding 55 to convert 10-15 to 'A'-'F'
        n >>= 4
    return s[::-1]  # Reverse the string