Declaraton:
    tuple<type, type, type> tp;

Inserting Data:
    tuple<type, type, type> tp = (val, val, val);
    OR, get<index>(tp) = val;
    OR, tp = make_tuple(val, val, val);

Accessing Data:
    auto [a, b, c] = tp;
    OR, get<index>(tp);

Tuple Dize:
    cout << tuple_size<decltype(tp)>::value;

Swapping:
    tp.swap(tp1);

Unpacking Tuple:
    int a; float b; char c;
    tuple<int, float, char> tp = (1, 2.5, 'a');
    tie(a, b, c) = tp;
    OR, tie(a, ignore, c) = tp;
    OR, auto [d, e, f] = tp;

Concatenating 2 tuples to return a new tuple:
    tuple<type, type, type> tp = (val, val, val);
    tuple<type, type, type> tp1 = (val, val, val);
    auto tp2 = tuple_cat(tp, tp1);