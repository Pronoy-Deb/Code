# Quadratic Equation: a*x^2 + b*x + c = 0;
# Complexity: O(log(D)), D = discriminant

import cmath
def sol(a, b, c):
    discriminant = b**2 - 4 * a * c
    dum = 2 * a; i1 = i2 = ""
    if discriminant > 0:
        sq_root = cmath.sqrt(discriminant)
        x1 = (-b + sq_root) / dum
        x2 = (-b - sq_root) / dum
    else:
        x1 = x2 = -b / dum
        if discriminant < 0:
            imaginary = str(cmath.sqrt(-discriminant) / dum)
            i1 = '+' + imaginary + 'i'
            i2 = '-' + imaginary + 'i'
    return (x1, i1), (x2, i2)

# Example usage
a, b, c = map(float, input().split())
(x1, i1), (x2, i2) = sol(a, b, c)
print(x1, i1)
print(x2, i2)

# Cubic Equation: a*x^3 + b*x^2 + c*x + d = 0;
# Complexity:

import cmath
def sol(a, b, c, d):
    b /= a; c /= a; d /= a
    q = (3 * c - b**2) / 9
    r = (-(27 * d) + b * (9 * c - 2 * b**2)) / 54
    disc = q**3 + r**2; term1 = b / 3; i1 = i2 = ""
    if disc > 0:
        sq_root = cmath.sqrt(disc)
        s = cmath.cbrt(r + sq_root)
        t = cmath.cbrt(r - sq_root)
        x = -term1 + s + t; term1 += (s + t) / 2
        x1 = x2 = -term1
        term1 = cmath.sqrt(3) * (t - s) / 2
        x1_imag = term1; x2_imag = -term1
        i1 = '+' + str(x1_imag) + 'i'
        i2 = '-' + str(x2_imag) + 'i'
    elif disc == 0:
        r13 = cmath.cbrt(r); x = -term1 + 2 * r13
        x1 = x2 = -(r13 + term1)
    else:
        q = -q; r13 = 2 * cmath.sqrt(q)
        dum1 = cmath.acos(r / cmath.sqrt(q**3))
        x = -term1 + r13 * cmath.cos(dum1 / 3)
        x1 = -term1 + r13 * cmath.cos((dum1 + 2 * cmath.pi) / 3)
        x2 = -term1 + r13 * cmath.cos((dum1 + 4 * cmath.pi) / 3)
    return x, (x1, i1), (x2, i2)

# Example usage
a, b, c, d = map(float, input().split())
x, (x1, i1), (x2, i2) = sol(a, b, c, d)
print(x)
print(x1, i1)
print(x2, i2)