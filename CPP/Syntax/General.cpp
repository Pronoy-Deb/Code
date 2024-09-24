// Note:
    1. No of triangles that can be formed without intersection in an n-armed polygon: n - 2

    -> To take input till EOF is found:
        C++: while(cin >> n) cout << n << '\n';
        C: while(scanf("%d", &n) != EOF) printf("%d\n", n);

    -> To take input of an unknown length stream:
        istreambuf_iterator<char> begin(cin), end;
        string s(begin, end);

    -> To detect a blank line while taking input:
        string s; cin.ignore(); getline(cin, s);
        if (s.empty()) cout << "Blank Line";

    -> To cause an assertion error if the condition is false:
        assert(condition);

    -> Checking whether the type mathces : // returns true/false
        cout << isalpha('a');  // A-Z, a-z
        cout << isalnum('A');  // 0-9, A-Z, a-z
        cout << isblank();  // \t
        cout << isdigit(1);  // 0-9
        cout << islower('a')  // a-z
        cout << isupper('A')  // A-Z
        cout << isxdigit('f')  // 0-9, A-F, a-f

    -> To set precision in floating point numbers:
        cout << fixed << setprecision(n);

    -> To see the type of a variable:
        cout << typeid(vari).name();

    -> To see the byte size of a data type:
        cout << sizeof(type);  // returns the byte size -> 1 byte = 8 bit

    -> Maximum squared number that fits in integer:
        31623 * 31623 = 1000014129 > 1e9

    -> sqrt(), sqrtl(), cbrt() and pow() function returns double type value

    -> The minimum integer = INT_MIN, The maximum integer = INT_MAX

    -> To print a new line based on one condition:
        cout << " \n"[i == n-1];

    -> ASCII Values of Characters:
        0-9 : 48-57, A-Z : 65-90, a-z : 97-122

    -> Maximum Numbers:
        int = 10^9, long long = 10^18, unsigned long long = 10^20

    -> min() & max() functions take data of same type

    -> Value of PI:
        const double pi = M_PI;
    OR, const double pi = acos(-1);

    -> Add the rounding down value:
        const double rd = 1e-9;

    -> For .txt type input/output:
        #ifdef LOCAL
        freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
        #endif

    -> printf(), scanf():
        void in(auto &n) {string s=typeid(n).name();if(s=="i")scanf("%d",&n);else if(s=="x")scanf("%lld",&n);else if(s=="c")scanf("%c",&n);else if(s=="b"){int t;scanf("%d",&t);n=t;}else if(s=="f")scanf("%f",&n);else if(s=="d")scanf("%lf",&n);else cin>>n;}
        void out(auto n) {string s=typeid(n).name();if(s=="i" or s=="b")printf("%d ",n);else if(s=="x")printf("%lld ",n);else if(s=="c")printf("%c",n);else if(s=="f")printf("%f",n);else if(s=="d")printf("%lf",n);else cout<<n;}

    -> To print the truth value of a number:
        cout << boolalpha << bool(n);

    -> LAMBDA function:
        [] (int a) {return a%2==0;}