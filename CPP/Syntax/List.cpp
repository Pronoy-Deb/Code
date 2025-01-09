Note:
    -> It is actually doubly linked list and not contigeous
    -> Elements cannot be accessed by index or O(1)

Declaration:
    list<type> ls;

Adding elements in the list:
    ls.emplace_back(ele); // adding in the back
    OR, ls.push_back(ele); // adding in the back
    ls.emplace_front(ele); // adding in the front
    OR, ls.push_front(ele); // adding in the front

Deleting elements from the list:
    ls.pop_back(ele); // deleting from the back
    ls.pop_front(ele); // deleting from the front
    ls.remove(ele); // deleting by value

Reversing a list:
    ls.reverse();

Sorting a list:
    ls.sort();

Inserting:
    auto it = ls.begin();
    advance(it, 3);
    ls.insert(it, 100);
    OR, ls.emplace(it, 100);

