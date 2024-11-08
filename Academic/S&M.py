# Mid-Square Method:

print("Enter the value of Z0: ", end=' ')
z0 = int(input()); i = 0
print("i  Zi\tUi\tZi*Zi")
while z0:
    print(i, z0, sep="  ", end='\t')
    if not i: print("--", end='\t')
    else: print(z0/10000, end='\t')
    z0 *= z0; s = str(z0)
    while len(s) < 8: s = '0' + s
    print(s); s = s[2:6]
    z0 = int(s); i += 1
print(i, " 0    0      00000000")

# Linear Congruential Method:

print("Enter the value of a, c and m:", end=' ')
a, c, m = map(int, input().split())
i = 0; xi1 = x01 = 1; xi2 = x02 = 2
xi3 = x03 = 3; xi4 = x04 = 4
ok1 = ok2 = ok3 = ok4 = 0
print("i Xi(X0=1) Xi(X0=2) Xi(X0=3) Xi(X0=4)")
while ok1 < 2 or ok2 < 2 or ok3 < 2 or ok4 < 2:
    print(i, end='\t'); i += 1
    print(xi1 if ok1 < 2 else '', end='\t')
    print(xi2 if ok2 < 2 else '', end='\t')
    print(xi3 if ok3 < 2 else '', end='\t')
    print(xi4 if ok4 < 2 else '')
    if not ok1: xi1 = (a * xi1 + c) % m
    if not ok2: xi2 = (a * xi2 + c) % m
    if not ok3: xi3 = (a * xi3 + c) % m
    if not ok4: xi4 = (a * xi4 + c) % m
    ok1 += xi1 == x01; ok2 += xi2 == x02
    ok3 += xi3 == x03; ok4 += xi4 == x04