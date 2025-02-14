// Note:
    -> If(a % x == 0) and (b % x == 0) then, (a + b) % x == 0, (a - b) % x == 0, (ab) % x == 0 and (ab) % (x * x) == 0
    -> Number of distinct multiple of a, b from 1 to n: (n / a) + (n / b) - (n / lcm(a, b));
    -> Increment 1 if there is a remainder: (n + k - 1) / k
    -> Largest prime that can be stored in int: 2147483647
    -> Largest prime that can be stored in unsigned int: 4294967291
    -> Largest prime that can be stored in long long: 9223372036854775783ll
    -> Largest prime that can be stored in unsigned long long: 18446744073709551557ll

// Syntax:
    Finding out the Number of Digits in a Number:
        (int)log10(n) + 1;

    To print the COMPOSITION of two integers as a double type value:
        long long a = 12, b = 345, digit = (!b ? 1 : (int)(log10(b)) + 1);
        double d = a + (b / pow(10, digit));
        cout << fixed << setprecision(digit) << d;  // 12.345

    Qoutient and remainder (Built-in):
        auto dv = div(a, b);
        cout << dv.quot << ' ' << dv.rem;

    GCD of two numbers:
        gcd(a, b)  // O(log(min(a,b))), gcd(0, n) = n

    LCM of two numbers:
        lcm(a, b);  OR,  (a * b) / gcd(a, b)

    To determine the QUBE-ROOT of a number:
        cbrt(number)  OR,  round(pow(n, 1/3.0))

    SWAPPING two numbers:
        swap(a, b);  OR,  a ^= b; b ^= a; a ^= b;

    To determine round value of a number:
        round(number);  // 2.3 -> 2, 2.5 -> 3, 2.7 -> 3

    nan and inf:
        cout << sqrt(-2); // prints nan
        cout << 2/0.0 // prints inf

    To check whether it is not a number (nan):
        cout << isnan(sqrt(-2)); // returns true

    Floor Division:
    long long fd(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    Ceil Division:
    long long cd(long long a, long long b) {
        return a / b + ((a ^ b) > 0 && a % b);
    }

    To convert a float value to its upper integer value:
        ((long long))ceil(n);  // 2.3 -> 3, Returns

    To convert a float value to its integer value:
        ((long long))floor(n);  // 2.3 -> 2

    To print a certain number of digits of a float type value:
        cout << setprecision(number_of_digits_both_sides_of_the_point) << n;

    To avoid SCIENTIFIC NOTATION of a number:
        cout << fixed << n;
        cout << fixed << setprecision(number of digits after the point) << n;

    Maximum of more than two elements:
        max({a, b, c, d, e});

    Minimum of more than two elements:
        min({a, b, c, d, e});

    Printing RANDOM numbers:
        cout << rand();

    To represent as MINIMUM FRACTION:
        a / b  ->  (a / gcd(a,b)) / (b / gcd(a,b))