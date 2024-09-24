#define pa(c)             \
    cerr << #c << " = ";  \
    for (auto &e : c)     \
        cerr << e << ' '; \
    cerr << '\n'

#define pn(c, n)             \
    cerr << #c << " = ";     \
    for (size_t i = 0; i < n; ++i)  \
        cerr << c[i] << ' '; \
    cerr << '\n'

#define pr(c)                \
    cerr << #c << " = ";     \
    bool flag = false;       \
    for (auto &r : c)        \
    {                        \
        if (flag)            \
            cerr << ", ";    \
        cerr << '{';         \
        bool flag2 = false;  \
        for (auto &e : r)    \
        {                    \
            if (flag2)       \
                cerr << ' '; \
            cerr << e;       \
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
    for (auto &[f, s] : c)   \
    {                        \
        if (flag)            \
            cerr << ", ";    \
        cerr << '(' << f << ", " << s << ")";         \
        flag = true;         \
    } \
    cerr << "}\n"

// Helper to identify if a type is an iterable container
template <typename T, typename = void>
struct is_iterable : false_type
{
};

template <typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type
{
};

// Helper to identify if a type is a map-like container
template <typename T, typename = void>
struct is_map : false_type
{
};

template <typename T>
struct is_map<T, void_t<typename T::key_type, typename T::mapped_type>> : true_type
{
};

// Helper to identify if a type is a 2D container
template <typename T, typename = void>
struct is_2d_container : false_type
{
};

template <typename T>
struct is_2d_container<T, void_t<typename T::value_type::value_type>> : is_iterable<typename T::value_type>
{
};

// Helper to identify if a type is a C-style array
template <typename T>
struct is_c_array : false_type
{
};

template <typename T, size_t N>
struct is_c_array<T[N]> : true_type
{
};

// Custom output function for pairs
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p)
{
    os << "{" << p.first << ' ' << p.second << "},";
    return os;
}

// Implementations for different types of containers
template <typename T>
void v_impl(auto *x, T &&y)
{
    cerr << x << " = " << y << ", ";
}

template <typename T, typename... Ts>
void v_impl(auto *x, T &&y, Ts &&...g)
{
    auto *c = strchr(x, ',');
    if (c)
    {
        string first_arg(x, c - x);
        v_impl(first_arg.c_str(), forward<T>(y));
        v_impl(c + 2, forward<Ts>(g)...);
    }
    else
    {
        v_impl(x, forward<T>(y));
    }
}

template <typename T>
void e_impl(auto *x, T &&y)
{
    cerr << '\n' << x << " = ";
    for (const auto &e : y)
        cerr << e << ' ';
}

template <typename T, size_t N>
void e_impl(auto *x, T (&y)[N])
{
    cerr << '\n' << x << " = ";
    bool flag = false;
    for (size_t i = 0; i < N; ++i)
    {
        if (flag)
            cerr << ", ";
        cerr << '{';
        bool flag2 = false;
        for (size_t j = 0; j < N; ++j)
        {
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
void e_impl(auto *x, T &&y, Ts &&...g)
{
    auto *c = strchr(x, ',');
    cerr << '\n';
    cerr.write(x, c ? c - x : strlen(x)) << " = ";
    for (const auto &e : y)
        cerr << e << ' ';
    if (c)
        e_impl(c + 2, forward<Ts>(g)...);
}

template <typename T>
void p_impl(auto *x, T &&y)
{
    cerr << '\n' << x << " = ";
    bool flag = false;
    for (const auto &[f, s] : y)
    {
        if (flag)
            cerr << ", ";
        cerr << '(' << f << " : " << s << ')';
        flag = true;
    }
}

template <typename T, typename... Ts>
void p_impl(auto *x, T &&y, Ts &&...g)
{
    auto *c = strchr(x, ',');
    cerr << '\n';
    cerr.write(x, c ? c - x : strlen(x)) << " = ";
    bool flag = false;
    for (const auto &[f, s] : y) {
        if (flag)
            cerr << ", ";
        cerr << '(' << f << " : " << s << ')';
        flag = true;
    }
    if (c)
        p_impl(c + 2, forward<Ts>(g)...);
}

template <typename T>
void r_impl(auto *x, T &&y)
{
    cerr << '\n'
         << x << " = ";
    bool flag = false;
    for (const auto &r : y)
    {
        if (flag)
            cerr << ", ";
        cerr << '{';
        bool flag2 = false;
        for (const auto &e : r)
        {
            if (flag2)
                cerr << ' ';
            cerr << e;
            flag2 = true;
        }
        cerr << "}";
        flag = true;
    }
}

template <typename T, typename... Ts>
void r_impl(auto *x, T &&y, Ts &&...g)
{
    auto *c = strchr(x, ',');
    cerr << '\n';
    cerr.write(x, c ? c - x : strlen(x)) << " = ";
    bool flag = false;
    for (const auto &r : y)
    {
        if (flag)
            cerr << ", ";
        cerr << '{';
        bool flag2 = false;
        for (const auto &e : r)
        {
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

void ck_impl(auto *x) {}

auto ck_impl(auto *x, auto &&y)
{
    if constexpr (is_2d_container<decay_t<decltype(y)>>::value)
    {
        r_impl(x, forward<decltype(y)>(y));
    }
    else if constexpr (is_map<decay_t<decltype(y)>>::value)
    {
        p_impl(x, forward<decltype(y)>(y));
    }
    else if constexpr (is_iterable<decay_t<decltype(y)>>::value)
    {
        e_impl(x, forward<decltype(y)>(y));
    }
    else
    {
        v_impl(x, forward<decltype(y)>(y));
    }
}

template <typename T, typename... Ts>
void ck_impl(auto *x, T &&y, Ts &&...g)
{
    auto *c = strchr(x, ',');
    if (c)
    {
        string first_arg(x, c - x);
        ck_impl(first_arg.c_str(), forward<T>(y));
        ck_impl(c + 2, forward<Ts>(g)...);
    }
    else
    {
        ck_impl(x, forward<T>(y));
    }
}

#define ck(...) ck_impl(#__VA_ARGS__, __VA_ARGS__); cerr << '\n'