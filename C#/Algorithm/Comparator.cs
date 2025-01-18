// Tuple of two elements: var tp = new List<Tuple<long, long>>();

// a.Item1.CompareTo(b.Item1); CompareTo returns:
    -1 if a.Item1 < b.Item1
    0 if they are equal
    1 if a.Item1 > b.Item1

// Sorts a list of tuples by the first element in ascending order and the second element in descending order

static int cmp((int, int) a, (int, int) b) {
    if (a.Item1 != b.Item1) return a.Item1.CompareTo(b.Item1);
    return b.Item2.CompareTo(a.Item2);
}

// Usage
tp.Sort(cmp);
