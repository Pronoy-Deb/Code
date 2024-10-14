// Note: Uses about (n / 64) memory than boolean array and can calculate upto 1e8 in 1 second

Default constructor initializes with all bits 0:
    bitset<32> bset1;

bset2 is initialized with bits of 20:
    bitset<32> bset2(20);

Initialized with bits of string:
    bitset<10> s(string("0010011010")); // from right to left
    cout << s[4] << "\n"; // 1
    cout << s[5] << "\n"; // 0

Count number of set bits:
    bitset<10> s(string("0010011010"));
    cout << s.count() << "\n"; // 4

Bitwise operations:
    bitset<10> a(string("0010110110"));
    bitset<10> b(string("1011011000"));
    cout << (a&b) << "\n"; // 0010010000
    cout << (a|b) << "\n"; // 1011111110
    cout << (a^b) << "\n"; // 1001101110