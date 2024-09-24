Syntax :
    Declaration :
        pr = pair_name
        pair<type, type> pr;
    
    ACCESSING the first and second element :
        pr.first,  pr.second

    ACCESSING the elements of a pair :
        pair<int, int> pr;
        for(auto it = pr.begin(); it != pr.end(); it++)
            cout << (it->first) << ' ' << (it->second);
        OR, cout << (*it).first << ' ' << (*it).second;
    
    To make a new pair :
        pr = make_pair(1, 1);

    To swap two pais of the same type :
        pr.swap(pr1);
        