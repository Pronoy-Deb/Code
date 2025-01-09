Note:
    1. Maximum Size of a Map : 2^30 or 10^9
    2. Complexity of inserting or accessing elements of an ordered map : O(nlog(n))
    3. Maps are designed according to "Red-Black Tree" structure.
    3. Unordered_Maps are designed according to "Hash Table" structure.
    4. Time complexity fluctuates for an unordered_map.

Syntax:
    mp = Map_name
    Declaring a Map:
        map<int, int> mp; // O(mp.size()), Sorted

    DECLARING a Map sorted in DESCENDING order:
        map<int, int, greater<>> mp;

    Declaring a Multimap:
        multimap<int, int> mp;  // allows duplicate keys

    Declaring an unordered map:
        unordered_map<int, int> mp;  // Unsorted

    Iterating over elements in map:
        if(mp.find(ele) != end(mp))  // mp[i] inserts the ele and then checks

    Inserting Key and Value in a Map:
        mp['a'] = 1;  // O(log(n))
        Or, mp.emplace('a', 1);  // O(log(n))
        Or, mp.insert({'a', 1});  // O(log(n))
        Or, mp.emplace(pair<char, int> ('a', 1));  // O(log(n))
        Or, mp.emplace("string", 1);  // O(s.size() * log(n))

    Finding a Value of a Map Using Its Key:
        mp['a']  // O(1) -> not always
        OR, mp.at('a')  // O(1), throws "out_of_range" exception if the key is absent
        mp.find('a') -> second;  // O(log(n))

    Erasing a key and its value:
        mp.erase(key); or, auto it = mp.find(key); mp.erase(it);  // O(log(n))

    Clearing a map:
        mp.clear();

    Printing the Keys and Values of a Map:
        for (auto &i : mp) cout << i.first << " : " << i.second;
        or, for(auto &[f,s] : mp) cout << f << " : " << s;
        or, for (auto i = begin(mp); i != end(mp); ++i)
                cout << i->first << " : " << i->second;

    Finding out the value of the maximum key of a Map:
        auto mx = max_element(begin(mp), end(mp), mp.value_comp());
	    cout << mx->first << " : " << mx->second << '\n';

    Maximum value of a map:
    Using comparator function:
        bool cmp(const pair<int, int> &a, const pair<int, int> &b)
            { return (a.second < b.second); }

        cout << max_element(begin(mp), end(mp), cmp) -> second;

    Using lambda function:
        cout << max_element(begin(mp), end(mp), [](const pair<int, int> &a, const pair<int, int> &b) -> bool
			{ return a.second < b.second; }) -> second;

    Printing LOWER_BOUND:
        mp.lower_bound(n);  // Returns lower_bound of the key

    Printing UPPER_BOUND:
        mp.upper_bound(n);  // Returns upper_bound of the key

    Sorting a map according to the VALUE:  // O(n*log(n))
    Using mutimap:
        multimap<int, int> mmp;  // ascending order
        multimap<int, int, greater<>> mmp;  // descending order
        for(auto [f, s] : mp) mmp.emplace(s, f);

    Using set of pairs:
        set<pair<int, int>> st; for (auto [f, s] : mp) st.insert({s, f});

    Using vector of pairs:
        vector<pair<int, int>> v(begin(mp), end(mp));
        sort(v.begin(), v.end(), [](const auto &a, const auto &b) { return a.second < b.second; });

    Accessing elements by their index :
        #include <ext/pb_ds/assoc_container.hpp>

        __gnu_pbds::tree<int, int, less<>, __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update> mp;

        auto it = mp.find_by_order(index);
        cout << it->first << " : " << it->second;  // Prints 0 : 0 if the index is out of bound
