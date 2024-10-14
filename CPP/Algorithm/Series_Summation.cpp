// Note:

* Summation of an arithmetic progression: n * (a + l) >> 1;  // n = number of terms, a = first term, l = last term

* Summation of a geometric progression: (l * r - a) / (r - 1);  // a = first term, l = last term, r = common ratio

* The sum of first n natural numbers:
    i = 1 + 2 + 3 + ... + n = (n * (n + 1)) >> 1;

* The sum of the squares of the first n natural numbers:
    i^2 = 1^2 + 2^2 + 3^2 + ... + n^2 = (n * (n + 1) * ((n << 1) + 1)) / 6;

* The sum of the cubes of the first n natural numbers:
    i^3 = 1^3 + 2^3 + 3^3 + ... + n^3 = (n * n * (n + 1) * (n + 1)) >> 2;

* The sum of the fourth powers of the first n natural numbers:
    i^4 = 1^4 + 2^4 + 3^4 + ... + n^4 = (1/30)*n*(n+1)*(2n+1)*((3*n*n)+(3*n)-1);

* The sum of the first n even natural numbers:
    2i = 2 + 4 + 6 + ... (n numbers) = n * (n + 1);

* The sum of the first n odd natural numbers:
    (2i-1) = 1 + 3 + 5 + .... (n numbers) = n * n;

* The sum of the arithmetic sequence a, a + d, a + 2d, ... , a + (n - 1) d:
    (n >> 1) * ((a << 1) + ((n - 1) * d));  // d = common difference, a = first element

* For the geometric sequence a, ar, ar^2, ... , ar^(n-1),
    The sum of the first n terms:  // r = common ratio, a = first element
    (a * (1 - (long long)pow(r, n))) / (1 - r);  // when r < 1
    (a * ((long long)pow(r, n) - 1)) / (r - 1);  // when r > 1

* The sum of the infinite terms, ∑∞ = a / (1 - r);  // only when |r| < 1

* 1 + 3 + 6 + 10 + 15 + ... + n = 1 + (1 + 2) + (1 + 2 + 3) + (1 + 2 + 3 + ... + n) + ... + n = (n * (n + 1) * (n + 2)) / 6