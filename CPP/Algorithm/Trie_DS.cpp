                    // To compute Maximum Xor Subarray:

long long trie[N][2], c = 0;
void insert(auto x) {
    long long nd = 0;
    for (int i = 30; i >= 0; --i) {
        int y = x >> i & 1;
        if (!trie[nd][y]) trie[nd][y] = ++c;
        nd = trie[nd][y];
    }
}
long long search(auto x) {
    long long ans = 0, nd = 0;
    for (int i = 30; i >= 0; --i) {
        int y = x >> i & 1;
        if (trie[nd][y ^ 1]) {
            nd = trie[nd][y ^ 1]; ans += (1ll << i);
        }
        else nd = trie[nd][y];
    }
    return ans;
}

// Operation:
    cin >> n;
    long long xr = 0, mx = 0; insert(xr);
    for (i = 0; i < n; ++i) {
        int x; cin >> x;
        xr ^= x; insert(xr);
        mx = max(search(xr), mx);
    }
    cout << mx;

// Problem: https://cses.fi/problemset/task/1655

                                    // OR,
struct Trie {
    static const long long B = 31;
    struct node {
        node* nxt[2];
        long long cnt;
        node() {
            nxt[0] = nxt[1] = NULL;
            cnt = 0;
        }
    } * root;
    Trie() { root = new node(); }
    void insert(long long val) {
        node* cur = root;
        cur->cnt++;
        for (int i = B - 1; i >= 0; --i) {
            int b = val >> i & 1;
            if (cur->nxt[b] == NULL) cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->cnt++;
        }
    }
    long long xormx(long long x) {
        node* cur = root;
        long long ans = 0;
        for (int i = B - 1; i >= 0; --i) {
            int k = x >> i & 1;
            if (cur->nxt[!k]) cur = cur->nxt[!k], ans <<= 1, ++ans;
            else cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }
    long long xormn(long long x) {
        node* cur = root;
        long long ans = 0;
        for (int i = B - 1; i >= 0; --i) {
            int k = x >> i & 1;
            if (cur->nxt[k]) cur = cur->nxt[k], ans <<= 1;
            else cur = cur->nxt[!k], ans <<= 1, ++ans;
        }
        return ans;
    }
    void del(node* cur) {
        for (int i = 0; i < 2; ++i)
            if (cur->nxt[i]) del(cur->nxt[i]);
        delete (cur);
    }
}
                            // OR,

struct Trie {
  static const int B = 31;
  struct node {
    node* nxt[2];
    int sz;
    node() {
      nxt[0] = nxt[1] = NULL;
      sz = 0;
    }
  }*root;
  Trie() {
    root = new node();
  }
  void insert(int val) {
    node* cur = root;
    cur -> sz++;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur -> nxt[b] == NULL) cur -> nxt[b] = new node();
      cur = cur -> nxt[b];
      cur -> sz++;
    }
  }
  int query(int x, int k) { // number of values s.t. val ^ x < k
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      if (cur == NULL) break;
      int b1 = x >> i & 1, b2 = k >> i & 1;
      if (b2 == 1) {
        if (cur -> nxt[b1]) ans += cur -> nxt[b1] -> sz;
        cur = cur -> nxt[!b1];
      } else cur = cur -> nxt[b1];
    }
    return ans;
  }
  int get_max(int x) { // returns maximum of val ^ x
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur -> nxt[!k]) cur = cur -> nxt[!k], ans <<= 1, ans++;
      else cur = cur -> nxt[k], ans <<= 1;
    }
    return ans;
  }
  int get_min(int x) { // returns minimum of val ^ x
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur -> nxt[k]) cur = cur -> nxt[k], ans <<= 1;
      else cur = cur -> nxt[!k], ans <<= 1, ans++;
    }
    return ans;
  }
  void del(node* cur) {
    for (int i = 0; i < 2; i++) if (cur -> nxt[i]) del(cur -> nxt[i]);
    delete(cur);
  }
} t;

// Operation:
    cin >> n >> k;
    long long ans = n * (n + 1) >> 1;
    int cur = 0; t.insert(cur);
    for (i = 0; i < n; ++i) {
        int x; cin >> x; cur ^= x;
        ans -= t.query(cur, k);
        t.insert(cur);
    }
    cout << ans << '\n';

                            // Another Approach:
// Note: Inserts, erases and searches strings in the trie

struct Trie {  // structure to store a Trie node
    bool isWord;  // true when the node completes a word
    map<char, Trie*> mp;  // each node stores a map to its child nodes
};
Trie* newNode() {  // Function that returns a new Trie node
    Trie* node = new Trie;
    node->isWord = false;
    return node;
}
auto insert(Trie*& head, const char* str) {  // Iterative function to insert a string into a Trie
    if (head == nullptr) head = newNode();
    Trie* curr = head;  // start from the root node
    while (*str) {
        if (curr->mp.find(*str) == curr->mp.end())  // create a new node if the path doesn't exist
            curr->mp[*str] = newNode();
        curr = curr->mp[*str];  // go to the next node
        ++str;  // move to the next character
    }
    curr->isWord = true;  // mark the current node as a leaf
}
auto haveChild(Trie const* curr) {  // Returns true if the given node has any children
    for (auto it: curr->mp) {
        if (it.second != nullptr) return true;
    }
    return false;
}
auto erase(Trie* &curr, const char* str) {  // Recursive function to delete a string from a Trie
    if (curr == nullptr) return false;  // return if Trie is empty
    if (*str) {  // if the end of the string is not reached
        if (curr!=nullptr && curr->mp.find(*str)!=curr->mp.end() && erase(curr->mp[*str],str+1) && curr->isWord==false) {
            if (!haveChild(curr)) {
                delete curr; curr = nullptr;
                return true;
            }
            else return false;
        }
    }
    if (*str == '\0' && curr->isWord) {  // if the end of the string is reached
        if (!haveChild(curr)) {  // if the current node is a leaf node and doesn't have any children
            delete curr; curr = nullptr;
            return true;  // delete the non-leaf parent nodes
        }
        else {  // if the current node is a leaf node and has children
            curr->isWord = false;  // mark the current node as a non-leaf node (DON'T DELETE IT)
            return false;  // don't delete its parent nodes
        }
    }
    return false;
}
auto search(Trie* head, const char* str) {  // Iterative function to search a string in a Trie
    if (head == nullptr) return false;  // return false if Trie is empty
    Trie* curr = head;
    while (*str) {
        curr = curr->mp[*str];  // go to the next node
        if (curr == nullptr) return false;  // if the string is invalid (reached end of a path in the Trie)
        ++str;  // move to the next character
    }
    return curr->isWord;  // return true if the current node is a leaf and the end of the string is reached
}

// Operation:
    Trie* head = nullptr;

    insert(head, "hello"); cout << search(head, "hello") << " ";  // prints 1
    insert(head, "helloworld"); cout << search(head, "helloworld") << " ";  // prints 1
    cout << search(head, "helll") << " ";  // prints 0 (Not present)
    insert(head, "hell"); cout << search(head, "hell") << " ";  // prints 1
    insert(head, "h"); cout << search(head, "h") << endl;  // prints 1 + newline
    erase(head, "hello"); cout << search(head, "hello") << " ";  // prints 0 (`hello` deleted)
    cout << search(head, "helloworld") << " ";  // prints 1
    cout << search(head, "hell") << endl;  // prints 1 + newline
    erase(head, "h"); cout << search(head, "h") << " ";  // prints 0 (`h` deleted)
    cout << search(head, "hell") << " ";  // prints 1
    cout << search(head, "helloworld") << endl;  // prints 1 + newline
    erase(head, "helloworld");
    cout << search(head, "helloworld") << " ";  // prints 0
    cout << search(head, "hell") << " ";  // prints 1
    erase(head, "hell"); cout << search(head, "hell") << endl;  // prints 0 + newline
    if (head == nullptr) cout << "Trie empty!!\n";  // Trie is empty now
    cout << search(head, "hell");  // prints 0