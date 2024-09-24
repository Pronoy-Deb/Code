Note:
    1. Vector and map initializes with all values as 0
    2. If there is no element exists in the vector or the string,
        the index() function returns n(the size of the vector)
    3. The count() function returns a long long type data
    4. Size of a vector: v.size()  // Complexity: O(1)

Syntax:
    DECLARING a Vector:
        vector<Data_Type> v; // Without size
        vector<Data_Type> v(n); // With size n and all elements 0
        vector<Data_Type> v(n, ele); // With size n and all elements ele

    PRINTING a 1D vector:
        for (const auto &i : v) cout<<i<<' '; cout<<'\n';

    DECLARING a 2D Vector (Vector of Vector):
        vector<vector<int>> v; // Operates like a python list
    
    DECLARAING a 2D Vector with initial size:
        vector<vector<type>> v(row_size, vector<type>(col_size));

    DECLARAING a 2D Vector with initial size and element:
        vector<vector<type>> v(row_size, vector<type>(col_size, ele));

    Taking INPUT of a 2D vector:
        vector<vector<int>> v;
        for(int i=0; i<n; ++i) {
            vector<int> tmp;
            for(int j=0; j<m; ++j) {
                int a; cin>>a; tmp.emplace_back(a);
            }
            v.emplace_back(tmp);
        }

    OR,

        for(int i=0; i<n; ++i) {
            v.emplace_back(vector<int> ());  // Pushing an empty vector
            for(int j=0; j<m; ++j) {
                int a; cin>>a; v[i].emplace_back(a);
            }
        }

    PRINTING a 2D vector:
        for(auto &i:v) { for(auto &j:i) cout<<j<<' '; cout<<'\n'; }

    ADDING Elements in a Vector:
        v.emplace_back(element);
        OR, v.push_back(element);
    
    DELETING the last element:
        v.pop_back();

    ADDING Elements in a vector from the BEGINNING:
        v.emplace(v.begin(), element);
        OR, v.insert(v.begin(), element);

    ADDING n copies of Elements in a vector from the BEGINNING:
        v.emplace(v.begin(), number_of_copies, element);
        OR, v.insert(v.begin(), number_of_copies, element);

    MAXIMUM Element of a Vector:
        *max_element(v.begin(), v.end());

    INDEX of the Maximum Element of a Vector:
        max_element(v.begin(), v.end()) - v.begin();

    MINIMUM Element of a Vector:
        *min_element(v.begin() , v.end());
    
    INDEX of the Minimum Element of a Vector:
        min_element(v.begin(), v.end()) - v.begin();
    
    INDEX of any Element of a Vector:
        find(v.begin(), v.end(), n) - v.begin();

    COUNTING the frequency of an element:
        count(v.begin(), v.end(), ele)
    
    To Shuffle the Elements of a Vector:
        random_shuffle(v.begin(), v.end());

    UPPER BOUND of an element:
        upper_bound(v.begin(), v.end(), n) - v.begin();

    LOWER BOUND of an element:
        lower_bound(v.begin(), v.end(), n) - v.begin();

    REVERSING a Vector:
        reverse(v.begin(), v.end());
    
    SUMMATION of Element of a Vector:
        sum = accumulate(v.begin(), v.end(), 0LL);
    
    Checking whether a vector is sorted in ASCENDING order:
        is_sorted(v.begin(), v.end());

    Checking whether a vector is sorted in DESCENDING order:
        is_sorted(v.rbegin(), v.rend());

    Determining the PRESENCE of an element using binary search:  // Sorted vector
        sort(v.begin(), v.end());
        binary_search(v.begin(), v.end(), ele);  // returns 0 or 1
    
    ERASING an element using its index:  // v.size()--
        v.erase(v.begin() + ind);
    
    ERASING all occurances of an element:
        v.erase(remove(v.begin(), v.end(), n), v.end());
    
    ERASING all duplicate elements:
        sort(v.begin(), v.end());  OR,  sort(rv.begin(), rv.end());
        v.erase(unique(v.begin(), v.end()), v.end());

    CLEARING a vector:
        v.clear();

    COPYING a vector to another:
        vector<int> v(v1);  OR,  v = v1;

    SORTING a vector or, (vector of pair according to first element) in ascending order:
    Complexit: O(n * log(n))
        sort(v.begin(), v.end());
        sort(v.begin() + range, v.end() - range);  // Range Based
        sort(v.begin(), v.end(), less());
    
    SORTING a vector or, (vector of pair according to first element) in descending order:
    Complexity: O(n*log(n))
        sort(rv.begin(), rv.end());
        sort(rv.begin() + range, rv.end() - range)  // Begins from the End
        sort(v.begin(), v.end(), greater());

    FILLING a vector with a number:
        fill(v.begin(), v.end(), n);
        fill(v.begin() + range, v.end() - range, n)  // Range Based

    SWAPPING two vectors:
        v.swap(v1);

    ASSIGNING an element n times in a vector:
        v.assign(n, element);
    
    RESIZING a vector:
        v.resize(new_size);

    Use of all_of() function:
        all_of(v.begin(), v.end(), [](int a){return a>0;})  // Returns 0/1
    
    Use of any_of() function:
        any_of(v.begin(), v.end(), [](int a){return a>0;})  // Returns 0/1
    
    Use of none_of() function:
        none_of(v.begin(), v.end(), [](int a){return a>0;})  // Returns 0/1

    Resizing a vector only with its UNIQUE elements (Set):
        sort(v.begin(), v.end());
        v.resize(distance(v.begin(),unique(v.begin(), v.end())));

    Storing increasing sequence :
        vector<int> v(n); iota(v.begin(), v.end(), starting_value);