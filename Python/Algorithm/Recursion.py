# usage - please remember to YIELD to call and return

from types import GeneratorType
def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack: return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to); to = next(to)
                else:
                    if stack: stack.pop()
                    if not stack: break
                    to = stack[-1].send(to)
            return to
    return wrappedfunc
@bootstrap

# Uses yield in the recursion

# OR,

from threading import Thread, stack_size; stack_size(M)
from sys import setrecursionlimit; setrecursionlimit(M)

# Uses return in the recursion

    while t <= tc: Thread(target=test(t)).start(); t += 1