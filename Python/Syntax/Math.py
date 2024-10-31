# Maximum of several numbers:
    max(a, b, c, d)

# Minimum of several numbers:
    min(a, b, c, d)

# Checking a number whether it is resulted by a power of 2:
    if n&(n-1) == 0:

# Determining the GCD of several numbers :
    math.gcd(n,n1,n2)

# Summation of digits of a number :
    ls = list(map(int, str(number).strip()))
    print(sum(ls))

# Printing a floating point number with precision 2 :
    print('%.2f' %n)  OR,  print("{0:.2f}".format(n))  OR,  print(round(n, 2))

# Calculating exponential value of n (e^n) :
    print(math.exp(n))

# Truncating, ceiling and flooring :
    math.trunc(n);  math.ceil(n);  math.floor(n)