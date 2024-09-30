// Note: Uses about (n / 64) memory than boolean array and can calculate upto 1e8 in 1 second

Default constructor initializes with all bits 0:
    bitset<32> bset1;

bset2 is initialized with bits of 20:
    bitset<32> bset2(20);

Initialized with bits of string:
    bitset<32> bset3(string("1100"));
