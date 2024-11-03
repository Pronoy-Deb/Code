from random import randint, seed
# def ranc(l, r): # All lowercase letters
#     from string import ascii_lowercase; from random import choise
#     return choise(ascii_lowercase)
# def ranr(l, r): return uniform(l, r)
M, N = int(1e9) + 7, int(2e5) + 5

def test():
    print(1) # For testcase input
    n = randint(1, 10); print(n)
    # k = ran(1, 5); print(k)
    for _ in range(n):
        print(randint(1, 10), end=' ')
    print()
    # st = set()
    # while len(st) != n:
    #     a = ran(1, 30)
    #     if a not in st:
    #         print(a, end=' ')
    #         st.add(a)
    # print()

if __name__ == "__main__":
    seed(); test()
