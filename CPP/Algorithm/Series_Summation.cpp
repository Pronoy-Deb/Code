Note:

1. The sum of first n natural numbers is calculated using the formula:
    ∑n = i = 1 + 2 + 3 + ... + n = (n * (n + 1)) >> 1;

2. The sum of the squares of the first n natural numbers is calculated using the formula:
    ∑n = i^2 = 1^2 + 2^2 + 3^2 + ... + n^2 = (n * (n + 1) * ((n << 1) + 1)) / 6;

3. The sum of the cubes of the first n natural numbers is calculated using the formula:
    ∑n = i^3 = 1^3 + 2^3 + 3^3 + ... + n^3 = (n * n * (n + 1) * (n + 1)) >> 2;

4. The sum of the fourth powers of the first n natural numbers is calculated using the formula:
    ∑n = i^4 = 1^4 + 2^4 + 3^4 + ... + n^4 = (1/30)*n*(n+1)*(2n+1)*((3*n*n)+(3*n)-1);

5. The sum of the first n even natural numbers is:
    ∑n = 2i = 2 + 4 + 6 + ... (n numbers) = n * (n + 1);

6. The sum of the first n odd natural numbers is:
    ∑n = (2i-1) = 1 + 3 + 5 + .... (n numbers) = n * n;

7. The sum of the arithmetic sequence a, a + d, a + 2d, ... , a + (n - 1) d is:
    ∑n = (n >> 1) * ((a << 1) + ((n - 1) * d));  // d = common difference, a = first element

8. For the geometric sequence a, ar, ar^2, ... , ar^(n-1),
    The sum of the first n terms is:  // r = common ratio, a = first element
    ∑n = (a * (1 - (long long)pow(r, n))) / (1 - r);  // when r < 1
    ∑n = (a * ((long long)pow(r, n) - 1)) / (r - 1);  // when r > 1

9. The sum of the infinite terms is, ∑∞ = a / (1 - r);  // only when |r| < 1

10. 1 + 3 + 6 + 10 + 15 + ... + n = 1 + (1 + 2) + (1 + 2 + 3) + (1 + 2 + 3 + ... + n) + ... + n = (n * (n + 1) * (n + 2)) / 6