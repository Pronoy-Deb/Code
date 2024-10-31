# Note:
    Maximum size of a list: 10 ^ 18

# General:
    # File I/O:
    from sys import stdin, stdout
    stdin = open('input.txt', 'r')
    stdout = open('output.txt', 'w')

    # Fast Input:
    input = sys.stdin.buffer.readline

    # Fast Output:
    out = lambda x: stdout.write(' '.join(map(str, x)) + '\n' if isinstance(x, list) else str(x) + '\n')

    # Taking multiple values as input in one line:
        a, b, c = map(int, input().split())
        OR, a, b, c = [int(i) for i in input().split()]

    # Read Until EOF
    import sys
    for line in sys.stdin:
        # This loop will run until the input reaches the end.
        # Do something with the line variable here.

    # e - notation:
        1000 == 1e3

    # Writing multiline comments:
        """                 """

    # ASCII value of a character:
        ord('character')

    # Checking the type of a container :
        print(type(container))

# Python User ID:
#     Bullet, kclee2172, zii.hrs, rishabhxchoudhary, Moody_in_a_hoodie, pajenegod,