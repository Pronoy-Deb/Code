// Maximum number that fits in an integer:
    int maxInt = int.MaxValue;

// Maximum number that fits in a long:
    long maxLong = long.MaxValue;

// Minimum number that fits in an integer:
    int minInt = int.MinValue;

// Minimum number that fits in a long:
    long minLong = long.MinValue;

// To determine the absolute value of a number:
    int absolute = Math.Abs(-5);

// To determine the square root of a number:
    double sqrt = Math.Sqrt(25);

// To determine the power of a number:
    double power = Math.Pow(2, 3);

// To determine the logarithm of a number:
    double log = Math.Log(8, 2);

// To determine the greatest common divisor of two numbers:
    int gcd = Math.GCD(12, 18);

// To determine the least common multiple of two numbers:
    int lcm = Math.LCM(12, 18);

// To determine if a number is prime:
    bool isPrime = Math.IsPrime(7);

// To generate a random number between 0 (inclusive) and 1 (exclusive):
    double random = new Random().NextDouble();

// To generate a random number between a specified range:
    int randomInRange = new Random().Next(1, 11);

// To round a number to the nearest integer:
    int rounded = (int)Math.Round(3.7);

// To calculate the factorial of a number:
    int factorial = Math.Factorial(5);

// To calculate the sum of all prime numbers between 1 and 100:
    int sum = Math.PrimeSum(100);

// To calculate the sum of all Fibonacci numbers between 1 and 100:
    int sum = Math.FibonacciSum(100);

// To calculate the sum of all numbers between 1 and 100 that are divisible by 3 or 5:
    int sum = Math.MultipleSum(100, 3, 5);

// To calculate the sum of all numbers between 1 and 100 that are divisible by 3, 5, or 7:
    int sum = Math.MultipleSum(100, 3, 5, 7);

// To calculate the sum of all numbers between 1 and 100 that are not divisible by 3:
    int sum = Math.NonMultipleSum(100, 3);
