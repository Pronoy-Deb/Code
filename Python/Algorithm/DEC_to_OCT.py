# Complexity: O(n)

def oct(n):
    if n == 0: return "0"
    s = ""
    while n:
        s += chr(n % 8 + 48)  # Adding 48 to convert digit to ASCII
        n >>= 3  # Shifting right by 3 bits (equivalent to dividing by 8)
    return s[::-1]  # Reverse the string

string oct(int n) {
    string s;
    while(n) {
        s += (n%8 + 48); n >>= 3;
    }
    reverse(s.begin(), s.end()); return s;
}