// Complexity: O(3^n)

    cin >> n;
    for (int mask = 0; mask < (1 << n); ++mask) {
        cout << mask << ": \n";
        for (int sm = mask; sm; sm = (sm - 1) & mask) {
            cout << '\t';
            for (int i = n - 1; i >= 0; --i)
                cout << bool(sm & (1 << i));
            cout << '\n';
        }
    }