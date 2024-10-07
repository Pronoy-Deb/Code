Syntax:
    Declaration:
        stack<type> sk;

    Pushing an element:
        sk.emplace(ele);
        OR, sk.push(ele);

    Value of the top:
        sk.top();

    Deleting an element:
        sk.pop();

    Checking the emptiness:
        sk.empty();  // Returns 0/1

// To increase the recursion stack size:
    Command on the terminal: ulimit -s unlimited
    Commnad while compiling: -Wl,--stack=268435456

    // Function:

    #include <sys/resource.h>
    void ss() {
        rlim_t stack_size = INT_MAX; struct rlimit rl;
        int res = getrlimit(RLIMIT_STACK, &rl);
        if (!res and rl.rlim_cur < stack_size) {
            rl.rlim_cur = stack_size; res = setrlimit(RLIMIT_STACK, &rl);
        }
    }
