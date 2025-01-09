// Note:
    1. XOR Operations:
        n ^ n = 0
        0 ^ n = n
        Even ^ 1 = Even + 1
        Odd ^ 1 = Odd - 1
        Even ^ (Even + 1) = 1
        Odd ^ (Odd + 1) = Odd + (Odd + 1)

    2. n *= 2  ->  n <<= 1,  n /= 2  ->  n >>= 1

    3. Logical and bitwise alternative operators:
        and, and_­eq, bitand, bitor, compl, not, not_­eq, or, or_­eq, xor, xor_­eq

    4. The maximum number that can be stored in an n-bit binary number:
        2^n - 1;  // For 4-bit -> 15 = 1 1 1 1

    5. INT_MAX = (1LL << 31) - 1 = pow(2, 31) - 1;  // 1 bit used for the sign(0 -> (+)ve, 1 -> (-)ve)

    6. a | b = a ^ b + a & b
    a ^ (a & b) = (a | b) ^ b
    b ^ (a & b) = (a | b) ^ a
    (a & b) ^ (a | b) = a ^ b

    7. Addition:
    a + b = a | b + a & b
    a + b = a ^ b + 2(a & b)

    8. Subtraction:
    a - b = (a ^ (a & b)) - ((a | b) ^ a)
    a - b = ((a | b) ^ b) - ((a | b) ^ a)
    a - b = (a ^ (a & b)) - (b ^ (a & b))
    a - b = ((a | b) ^ b) - (b ^ (a & b))

// Syntax:
    Checking whether a number is EVEN:
        if(~n & 1)

    Checking whether a number is ODD:
        if(n & 1)

    To DERIVE a number as the POWER of 2:
        pow(2, n)  ->  (1 << n)

    To check whether a number is a POWER of 2:
        if(n && !(n & (n - 1)))  // true

    To count the HIGH bits(1) in a number:
        __builtin_popcount(n);    // O(log(n)), For integer number
        __builtin_popcountll(n);  // O(log(n)), For long long number

    To count the LOW bits(0) in a number:
        __builtin_ctz(n);  // O(log(n))

    Finding out the Number of Bits in a Number:
        (int)log2(n) + 1;

    To check is divisible by power of 2^k:
        !(n & ((1ll << k) - 1)) // true

    To convert a DECIMAL number into BINARY string:
        string s = bitset<8>(n).to_string();

    To check the bitwise POSITION (i-th bit) of a number is whether high or low:  // 0 or 1
        (n & (1 << i)) ? 1 : 0;  OR, (n & (1LL << i)) ? 1 : 0;  // for long long

    To SET the i-th bit:
        n |= (1 << i);  OR,  n |= (1LL << i);  // -> For long long

    To UNSET the i-th bit:
        n &= (~(1 << i));  OR,  n &= (~(1LL << i));

    To TOGGLE [0 <-> 1] the i-th bit:
        n ^ (1 << i);  OR,  n ^ (1LL << i);

    To Strip/Unset the LOWEST/LAST SET BIT:
        n &= (n - 1);

    To Strip/Unset the HIGHEST/FIRST SET BIT:
        n &= ~(n & (n - 1));

    To get the LOWEST/LAST SET BIT:
        n &= (-n);

    To get the HIGHEST/FIRST SET BIT:
        n &= ~(n - 1);

    To convert a BINARY string into DECIMAL number:
        unsigned long n = bitset<64>(s).to_ulong();

    To print a DECIMAL number in HEXADECIMAL form:
        cout << hex << decimal_number;  // In lowercase

    To convert a HEXADECIMAL number into DECIMAL:
        int n; istringstream("hex_num") >> hex >> n; cout << n;

    To print a DECIMAL number in OCTAL form:
        cout << oct << decimal_number;

    To convert a OCTAL number into DECIMAL:
        int n; istringstream("oct_num") >> oct >> n; cout << n;

    To perform the ARITHMATIC operations (Mul or Div by 2) k number of times:
        Multiplication: (n <<= k)  // for(int i = 1; i <= k; ++i) n *= 2;
        Division: (n >>= k)  // for(int i = 1; i <= k; ++i) n /= 2;

    To SET n bits from right to left till i (LSB) of a number:
        n |= ((1 << i) - 1);

    To SET n bits from left to right till i (MSB) of a number:
        n |= (~((1 << (N - i)) - 1));  // N = Number of total bits

    To UNSET n bits from right to left till i (LSB) of a number:
        n &= (~((1 << i) - 1));

    To UNSET n bits from left to right till i (MSB) of a number:
        n &= ((1 << (N - i)) - 1);  // N = Number of total bits

    To only set the MSB:
        n &= (1ll << (int)log2(n));

    To only set the LSB:
        n &= (1ll << __builtin_ctzll(n));