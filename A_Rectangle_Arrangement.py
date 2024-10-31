M, N = 1000000007, 200005

def test(tc):
    n = int(input())
    # ls = list(map(int, input().split()))
    c = d = 0
    for _ in range (n):
        a, b = map(int, input().split())
        c = max(c, a)
        d = max(d, b)
    print((c + d) << 1)

if __name__ == "__main__":
    t = tc = 1
    tc = int(input())
    while t <= tc: test(t); t += 1