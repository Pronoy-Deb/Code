// Declaration:
    var dc = new Dictionary<int, int>();
    var dc = new SortedDictionary<int, int>(); // SortedDictionary

// Operations:
    dc.Add(x, y); // Add x, y pair in the dictionary
    dc.Remove(x); // Remove x, y pair from the dictionary
    int y = dc[x]; // Get value for key x
    bool exists = dc.ContainsKey(x); // Check if key x exists in the dictionary
    bool existsValue = dc.ContainsValue(y); // Check if value y exists in the dictionary
    int n = dc.Count; // Get the number of elements in the dictionary
    dc.Clear(); // Remove all elements from the dictionary
    // Traverse all
    // foreach (KeyValuePair<int, int> pr in dc) {
    // foreach (DictionaryEntry pr in dc) {
    foreach (var pr in dc) {
        Console.WriteLine("Key: " + pr.Key + ", Value: " + pr.Value);
    }

// 2-D Dictionary:
    var dc = new Dictionary<string, List<int>>();
    OR, var dc = new Dictionary<string, List<int>>(n); // 2-D dictionary of size n
    dc[key].Add(x); // Add element x to the list associated with key
    dc[key].RemoveAt(i); // Remove element at index i from the list associated with key
    int x = dc[key][i]; // Get element at index i from the list associated with key
    int n = dc[key].Count; // Get the number of elements in the list associated with key