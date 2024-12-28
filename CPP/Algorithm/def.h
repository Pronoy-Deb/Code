
#define pa(c) cerr << #c << " = { "; for (auto &e : c) cerr << e << ' '; cerr << "}\n"

#define pn(c, n) cerr << #c << " = { "; for (int l = 0; l < n; ++l) cerr << c[l] << ' '; cerr << "}\n"

#define pr(c)                \
    cerr << #c << " = ";     \
    bool flag = false;       \
    for (auto &r : c) {      \
        if (flag)            \
            cerr << ", ";    \
        cerr << '{';         \
        bool flag2 = false;  \
        for (auto &e : r) {  \
            if (flag2)       \
                cerr << ' '; \
            cerr << e;       \
            flag2 = true;    \
        }                    \
        cerr << '}';         \
        flag = true;         \
    }                        \
    cerr << '\n'

#define prc(c, n, m)         \
    cerr << #c << " = ";     \
    bool flag = false;       \
    for (size_t x = 0; x < n; ++x) { \
        if (flag)            \
            cerr << ", ";    \
        cerr << '{';         \
        bool flag2 = false;  \
        for (size_t y = 0; y < m; ++y) { \
            if (flag2)       \
                cerr << ' '; \
            cerr << c[x][y]; \
            flag2 = true;    \
        }                    \
        cerr << '}';         \
        flag = true;         \
    }                        \
    cerr << '\n'

#define pp(c)                \
    cerr << #c << " = ";     \
    bool flag = false;       \
    cerr << '{';             \
    for (auto &[f, s] : c) { \
        if (flag)            \
            cerr << ", ";    \
        cerr << '(' << f << ", " << s << ")"; \
        flag = true;         \
    } \
    cerr << "}\n"

// Helper to identify if a type is an iterable container
template <typename T, typename = void>
struct is_iterable : false_type {};

template <typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

template <typename T, typename = void>
struct is_pbds_tree_set : false_type {};

// // Specialization for PBDS sets
// template <typename Key, typename Value, typename Cmp, typename Tag, template <typename, typename, typename, typename> class Node_Update, typename Allocator>
// struct is_pbds_tree_set<tree<Key, Value, Cmp, Tag, Node_Update, Allocator>> : true_type {};

// Helper to identify if a type is a map-like container
template <typename T, typename = void>
struct is_map : false_type {};

template <typename T>
struct is_map<T, void_t<typename T::key_type, typename T::mapped_type>> : true_type {};

// Helper to identify if a type is a 2D container
template <typename T, typename = void>
struct is_2d_container : false_type {};

template <typename T>
struct is_2d_container<T, void_t<typename T::value_type::value_type>> : is_iterable<typename T::value_type> {};

// Helper to identify if a type is a C-style array
template <typename T>
struct is_c_array : false_type {};

template <typename T, size_t N>
struct is_c_array<T[N]> : true_type {};

// Helper to identify if a type is a stack
template <typename T>
struct is_stack : false_type {};

template <typename T, typename Container>
struct is_stack<stack<T, Container>> : true_type {};

// Helper to identify if a type is a queue
template <typename T>
struct is_queue : false_type {};

template <typename T, typename Container>
struct is_queue<queue<T, Container>> : true_type {};

template <typename T>
struct is_string : false_type {};

template <>
struct is_string<string> : true_type {};

// Printing strings
void string_impl(auto *x, string &y) {
    cerr << x << " = \"" << y << "\"\n";
}

// Printing stacks
template <typename T>
void stack_impl(auto *x, stack<T> y) {
    cerr << x << " = [";
    while (!y.empty()) {
        cerr << y.top();
        y.pop();
        if (!y.empty()) cerr << ", ";
    }
    cerr << "]\n";
}

// Printing queues
template <typename T>
void queue_impl(auto *x, queue<T> y) {
    cerr << x << " = [";
    while (!y.empty()) {
        cerr << y.front();
        y.pop();
        if (!y.empty()) cerr << ", ";
    }
    cerr << "]\n";}

// Custom output function for pairs
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
    os << "{" << p.first << ' ' << p.second << "},";
    return os;}

// Implementations for different types of containers
template <typename T>
void v_impl(auto *x, T &&y) {
    cerr << x << " = " << y << '\n';
}

template <typename T, typename... Ts>
void v_impl(auto *x, T &&y, Ts &&...g) {
    auto *c = strchr(x, ',');
    if (c) {
        string first_arg(x, c - x);
        v_impl(first_arg.c_str(), forward<T>(y));
        v_impl(c + 2, forward<Ts>(g)...);
    }
    else {
        v_impl(x, forward<T>(y));
    }}

template <typename T>
void e_impl(auto *x, T &&y) {
    cerr << x << " = { ";
    for (const auto &e : y) cerr << e << ' ';
    cerr << "}\n";
}

template <typename T, size_t N>
void e_impl(auto *x, T (&y)[N]) {
    cerr << x << " = ";
    bool flag = false;
    for (size_t i = 0; i < N; ++i) {
        if (flag)
            cerr << ", ";
        cerr << '{';
        bool flag2 = false;
        for (size_t j = 0; j < N; ++j) {
            if (flag2)
                cerr << ' ';
            cerr << y[i][j];
            flag2 = true;
        }
        cerr << '}';
        flag = true;
    }
}

template <typename T, typename... Ts>
void e_impl(auto *x, T &&y, Ts &&...g) {
    auto *c = strchr(x, ',');
    cerr.write(x, c ? c - x : strlen(x)) << " = ";
    for (const auto &e : y) cerr << e << ' ';
    if (c) e_impl(c + 2, forward<Ts>(g)...);
}

template <typename T>
void p_impl(auto *x, T &&y) {
    cerr << x << " = ";
    bool flag = false;
    for (const auto &[f, s] : y) {
        if (flag) cerr << ", ";
        cerr << '(' << f << " : " << s << ')';
        flag = true;
    }
}

template <typename T, typename... Ts>
void p_impl(auto *x, T &&y, Ts &&...g) {
    auto *c = strchr(x, ',');
    cerr.write(x, c ? c - x : strlen(x)) << " = ";
    bool flag = false;
    for (const auto &[f, s] : y) {
        if (flag) cerr << ", ";
        cerr << '(' << f << " : " << s << ')';
        flag = true;
    }
    if (c) p_impl(c + 2, forward<Ts>(g)...);
}

template <typename T>
void r_impl(auto *x, T &&y) {
    cerr << x << " = ";
    bool flag = false;
    for (const auto &r : y) {
        if (flag) cerr << ", ";
        cerr << '{';
        bool flag2 = false;
        for (const auto &e : r) {
            if (flag2) cerr << ' ';
            cerr << e;
            flag2 = true;
        }
        cerr << "}";
        flag = true;
    }
}

template <typename T, typename... Ts>
void r_impl(auto *x, T &&y, Ts &&...g) {
    auto *c = strchr(x, ',');
    cerr.write(x, c ? c - x : strlen(x)) << " = ";
    bool flag = false;
    for (const auto &r : y) {
        if (flag)
            cerr << ", ";
        cerr << '{';
        bool flag2 = false;
        for (const auto &e : r) {
            if (flag2)
                cerr << ' ';
            cerr << e;
            flag2 = true;
        }
        cerr << "}";
        flag = true;
    }
    if (c)
        r_impl(c + 2, forward<Ts>(g)...);
}

// Modified ck_impl function
void ck_impl(auto *x, auto &&y) {
    if constexpr (is_string<decay_t<decltype(y)>>::value) {
        string_impl(x, forward<decltype(y)>(y));
    } else if constexpr (is_stack<decay_t<decltype(y)>>::value) {
        stack_impl(x, forward<decltype(y)>(y));
    } else if constexpr (is_queue<decay_t<decltype(y)>>::value) {
        queue_impl(x, forward<decltype(y)>(y));
    } else if constexpr (is_2d_container<decay_t<decltype(y)>>::value) {
        r_impl(x, forward<decltype(y)>(y));
    } else if constexpr (is_pbds_tree_set<decay_t<decltype(y)>>::value || is_iterable<decay_t<decltype(y)>>::value || is_c_array<decay_t<decltype(y)>>::value) {
        e_impl(x, forward<decltype(y)>(y));
    } else if constexpr (is_map<decay_t<decltype(y)>>::value) {
        p_impl(x, forward<decltype(y)>(y));  // Handle regular maps
    } else {
        v_impl(x, forward<decltype(y)>(y));
    }
}

template <typename T, typename... Ts>
void ck_impl(auto *x, T &&y, Ts &&...g) {
    auto *c = strchr(x, ',');
    if (c) {
        string first_arg(x, c - x);
        ck_impl(first_arg.c_str(), forward<T>(y));
        ck_impl(c + 2, forward<Ts>(g)...);
    }
    else {
        ck_impl(x, forward<T>(y));
    }
}

#define ck(...) ck_impl(#__VA_ARGS__, __VA_ARGS__); cerr << '\n'