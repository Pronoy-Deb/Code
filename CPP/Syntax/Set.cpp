Note:
    1. Set initially remains sorted in ascending order
    2. Set & Multiset uses "Red-Black Tree" structure.
    3. Use find() instead of count() to determine the presence in set or multiset
    4. use st.lower_bound(n) to find the first element >= n; instead of lower_bound(st.begin(), st.end(), n);

Set:
    st = set_name
    DECLARATION of a set:
        set<int> st;  // O(log(n))
        set<int, greater<int>> st;  // Sorted in Descending order

    DECLARATION of an unordered set:
        unordered_set<int> st;  // O(1), WC : O(n)

    DECLARATION of a multiset:
        multiset<int> st;  // O(log(n)), Allows duplicate elements

    INSERTING an element:
        st.emplace(ele);  // O(log(n))
        OR, st.insert(ele);  // O(log(n))

    MAKING the set sorted in DESCENDING order:
        set<int, greater<int>> st;

    ERASING an element:  // O(log(n))
        st.erase(element);  // Erases all occurrences of the element in multiset
        auto it = st.find(element); st.erase(it)  // Erases one element, O(log(n))
        st.erase(starting_iterator, ending_iterator);  // removes from start to end-1

    FINDING an element:  // Returns iterator
        auto it = st.find(element);  // O(log(n))
        cout << (it != st.end() ? (*it) : -1);

        set.find(element)  // O(log(n))
        multiset.find(element)  // O(log(n))
        unordered_set.find(element)  // O(1), WC : O(n)

    Distance between two iterators: // O(n)
        distance(first_iterator, last_iterator);  // Returns the distance

    Printing LOWER_BOUND:
        st.lower_bound(n);

    Printing UPPER_BOUND:
        st.upper_bound(n);

    Set INTERSECTION operation:
        vector<int> v = {1,3,2,4}, v1 = {5,2,4}, vr(min(v.size(), v1.size()));
        sort(v.begin(), v.end()); sort(v1.begin(), v1.end());
        set_intersection(v.begin(), v.end(), v1.begin(), v1.end(), vr.begin());
        for(auto &i : vr) { if(!i) break; cout << i << ' '; }
        // for(auto i = vr.begin(); i != it; i++) cout << (*i) << ' ';

    Set UNION operation:
        vector<int> v = {1,3,2,4}, v1 = {5,2,4}, vr(v.size() + v1.size());
        sort(v.begin(), v.end()); sort(v1.begin(), v1.end());
        set_union(v.begin(), v.end(), v1.begin(), v1.end(), vr.begin());
        for(auto &i : vr) { if(!i) break; cout << i << ' '; }
        // for(auto i = vr.begin(); i != it; i++) cout << (*i) << ' ';

    Set DIFFERENCE operation:
        vector<int> v = {1,3,2,4}, v1 = {5,2,4}, vr(v.size());
        sort(v.begin(), v.end()); sort(v1.begin(), v1.end());
        set_difference(v.begin(), v.end(), v1.begin(), v1.end(), vr.begin());
        for(auto &i : vr) { if(!i) break; cout << i << ' '; }
        // for(auto i = vr.begin(); i != it; i++) cout << (*i) << ' ';

    Accessing elements by their index:
        #include <ext/pb_ds/assoc_container.hpp>

        __gnu_pbds::tree<int, __gnu_pbds::null_type, less<>, __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update> st;

        cout << *st.find_by_order(index);  // Prints 0 if the index is out of bound
