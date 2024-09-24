Syntax:
    Declaration:
        queue<type> q;  // queue
        deque<type> dq;  // deque

    PRIORITY QUEUE Declaration:  // O(log(n))
        priority_queue<type> pq;  // descending order
        priority_queue<int, deque<int>, greater<>> pq;  // ascending order
        priority_queue<int, vector<int>, greater<>> pq;  // ascending order
    
    Pushing an element:
        q.emplace(ele);  // For queue
        q.push(ele);  // For queue
        dq.emplace_back(ele)  // In the back for deque
        dq.push_back(ele)  // In the back for deque
        dq.emplace_front(ele)  // In the front for deque
        dq.push_front(ele)  // In the front for deque
    
    Front element of a queue:
        q.front();

    Back element of a deque:
        dq.back();

    DELETING an element from the rear :
        q.pop(); // For queue
        dq.pop_front(); // From the front for deque
        dq.pop_back(); // From the back for deque
