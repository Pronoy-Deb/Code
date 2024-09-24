# Complexity: O(1)
# 1. Solution of the equation: a*x = c;

def sol(a, c): return c / a

# 2. Solution of the equations: a1*x + b1*y = c1; a2*x + b2*y = c2;

def sol(a1, b1, c1, a2, b2, c2):
    den = a1 * b2 - a2 * b1
    if den == 0: return None
    x = (b2 * c1 - b1 * c2) / den
    y = (c2 * a1 - c1 * a2) / den
    return x, y

# 3. Solution of the equations: a1*x + b1*y + c1*z = d1;
    # a2*x + b2*y + c2*z = d2; a3*x + b3*y + c3*z = d3;

def det(mat):
    return (mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]))

def sol(co):
    d = [[co[i][j] for j in range(3)] for i in range(3)]
    d1 = [[co[i][3] if j == 0 else co[i][j] for j in range(3)] for i in range(3)]
    d2 = [[co[i][3] if j == 1 else co[i][j] for j in range(3)] for i in range(3)]
    d3 = [[co[i][3] if j == 2 else co[i][j] for j in range(3)] for i in range(3)]
    D = det(d)
    if D == 0: return None
    D1, D2, D3 = det(d1), det(d2), det(d3)
    x = D1 / D; y = D2 / D; z = D3 / D
    return x, y, z

# Gaussian Elimination Method:
# Complexity: O(n^3), N = 10
# Use: Used to solve n number of equations in order to find out n unknown values

def gaus(co):
    n = len(co)
    for k in range(n):
        i_max = max(range(k, n), key=lambda i: abs(co[i][k]))
        if co[i_max][k] == 0: return None
        co[k], co[i_max] = co[i_max], co[k]
        for i in range(k + 1, n):
            factor = co[i][k] / co[k][k]
            for j in range(k, n + 1):
                co[i][j] -= factor * co[k][j]
    x = [0] * n
    for i in range(n - 1, -1, -1):
        x[i] = co[i][n] / co[i][i]
        for j in range(i - 1, -1, -1):
            co[j][n] -= co[j][i] * x[i]
    return x