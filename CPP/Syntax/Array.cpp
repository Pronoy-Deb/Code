Note:
    1. Maximum Size of an Array: 10^6
    2. Maximum Size of a Boolean Array: 2 * 10^6
    3. Global array initializes with all elements as 0

Syntax:
    To Store 10^7 Elements in an Array Using Heap:
        int *ar = new int[10000000];

    Declaring an array:
        type name[size];  // 1D array
        OR, type name[size]{};  // Initializes all elements as 0
        OR, type name[row][column];  // 2D
        OR, type name[row][column]{};  // Initializes all elements as 0
        OR, array<type, column> name[row];

    Printing a 2-D array:
        for(auto &i : ar) { for(auto &j : i) cout<<j<<' '; cout<<'\n'; }

    Sorting array in Ascending Order:
        sort(ar, ar + n);

    Sorting array in Descending Order:
        sort(ar, ar + n, greater());

    Assigning All Elements as ele of a 1-D array:
        ar[size]{};  // assigns 0 at every index
        or, memset(ar, 0 / -1, sizeof ar);
        or, fill(ar, ar + n, ele);

    Assigning All Elements as ele of a 2-D Array:
        ar[r][c]{};  // Works only for assigning 0
        or, fill(&ar[0][0], &ar[0][0] + (r*c), ele);
        or, fill(&ar[0][0], &ar[0][0] + (sizeof(ar)/sizeof(ar[0][0])), ele);
        or, memset(ar, -1, sizeof(ar)); // Works only for 0 and -1

    Mamimum Element in an Array:
        *max_element(ar, ar + n);

    Index of the Maximum Element in an Array:
        max_element(ar, ar + n) - ar;

    Minimum Element in an Array:
        *min_element(ar, ar + n);

    Index of the Minimum Element in an Array:
        min_element(ar, ar + n) - ar;

    Index of any element of an Array:
        find(ar, ar + n, ele) - ar;

    Counting the Frequency of an Element in an Array:
        count(ar, ar + n, 1) //Counting the number of 1s

    Checking the Euality of Two Arrays arr & ar:
        if(equal(ar, ar + n, arr))

    Copying n Elements of an Array arr to Another Array ar:
        copy(arr, arr + n, ar);

    Finding out the length of an array:
        n = sizeof(ar) / sizeof(ar[0]);

    Summation of Elements of an Array:
        accumulate(ar, ar + n, 0LL);

    Rotating the Elements of an Array:
        rotate(ar, ar + 3, ar + n);

    To Shuffle the Elements of an Array:
        random_shuffle(ar, ar + n);

    UPPER BOUND of an element:
        upper_bound(ar, ar + n, ele) - ar;

    LOWER BOUND of an element:
        lower_bound(ar, ar + n, ele) - ar;

    REVERSING an array:
        reverse(ar, ar + n);

    Checking whether an array is sorted in ASCENDING order:
        is_sorted(ar, ar + n);

    Checking whether an array is sorted in DESCENDING order:
        is_sorted(ar, ar + n, greater());

    Determining the PRESENCE of an element using binary search:  // Sorted vector
        binary_search(ar, ar + n, ele);  // returns 0 or 1

    SWAPPING two arrays of the SAME SIZE:
        swap(ar, ar1);

    Use of all_of() function:
        all_of(ar, ar + n, [](int a){return a>0;})  // Returns 0/1

    Use of any_of() function:
        any_of(ar, ar + n, [](int a){return a>0;})  // Returns 0/1

    Use of none_of() function:
        none_of(ar, ar + n, [](int a){return a>0;})  // Returns 0/1

    Prefix / Cumulative sum:
        int ar[n] = {1,2,3,4}; long long sum[n+1]{};
        partial_sum(ar, ar + n, sum+1);

    Storing increasing sequence:
        int ar[n]; iota(ar, ar + n, starting_value);