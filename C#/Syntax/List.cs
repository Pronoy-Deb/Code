// Inlclusions:
    using System.Collections.Generic;

// List
    var ls = new List();
    OR, var ls = new List<int>(n); // List of size n
    ls.Add(x); // Add element x to the end of the list
    ls.RemoveAt(i); // Remove element at index i
    ls.Remove(10); // Remove element 10
    ls.RemoveRange(0, 2); // Remove elements in range [0, 2]
    int x = ls[i]; // Get element at index i
    int n = ls.Count; // Get the size of the list
    ls.Clear(); // Remove all elements from the list
    ls.Sort(); // Sort the list in ascending order
    ls.Reverse(); // Reverse the list
    ls.RemoveAll(x => x == y); // Remove all elements equal to y from the list
    // traverse all
    foreach (int i in ls) {
        Console.WriteLine(i);
    }

// 2-D List:
    var ls = new List<List<int>>(n); // List of size n, where each inner list is also a list
    ls[i].Add(x); // Add element x to the end of the i-th inner list
    ls[i].RemoveAt(j); // Remove element at index j from the i-th inner list
    int x = ls[i][j]; // Get element at index j of the i-th inner list
    int n = ls[i].Count; // Get the size of the i-th inner list
    ls[i].Clear(); // Remove all elements from the i-th inner list
    ls[i].Sort(); // Sort the i-th inner list in ascending order
    ls[i].Reverse(); // Reverse the i-th inner list
    ls[i].RemoveAll(x => x == y); // Remove all elements equal to y from the i-th inner list
    // traverse all
    foreach (var sublist in ls) {
        foreach (var i in sublist) {
            Console.WriteLine(i);
        }
    }

// SortedList:
    var ls = new SortedList();
    OR, var ls = new SortedList<int, string>(); // Sorted list
    ls.Add(1, "one"); // Add element (1, "one") to the sorted list
    ls.Remove(1); // Remove element (1, "one") from the sorted list
    int x = ls.Keys[i]; // Get the key at index i
    string y = ls.Values[i]; // Get the value at index i
    int n = ls.Count; // Get the size of the sorted list
    ls.Contains(key); // Checks whether the list contains key
    OR, ls.ContainsKey(key);
    ls.ContainsValue(val); // Checks whether the list contains value val
    ls.Clear(); // Remove all elements from the sorted list
    // Traversing the elements:
    foreach (var pair in ls) {
        Console.WriteLine("Key: " + pair.Key + ", Value: " + pair.Value);
    }

// LinkedList:
    var ls = new LinkedList<int>();
    OR, var ls = new LinkedList<int>(n); // LinkedList of size n
    ls.AddFirst(x); // Add element x to the beginning of the list
    ls.AddLast(x); // Add element x to the end of the list
    ls.RemoveFirst(); // Remove the first element from the list
    ls.RemoveLast(); // Remove the last element from the list
    ls.Remove(ls.First); // Remove the first element
    ls.Remove(x); // Remove the element x
    int x = ls.First.Value; // Get the first element
    int y = ls.Last.Value; // Get the last element
    int n = ls.Count; // Get the size of the list
    ls.Clear(); // Remove all elements from the list
    ls.Contains(x); // Check availability of x
    // Traversing the elements:
    foreach (var i in ls) {
        Console.WriteLine(i);
    }

// Queue: