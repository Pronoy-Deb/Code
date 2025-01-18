// Declaration:
    var tp = (x, y); // Create a tuple with two elements
    var tp = Tuple.Create(x, y); // Create a tuple with two elements
    var tp = Tuple.Create(x, y, z); // Create a tuple with three elements

// Accessing elements:
    int x = tp.Item1; // Get the first element
    int y = tp.Item2; // Get the second element

// Array of tuples:
    var tp = new (int, int)[n]; // Array of n tuples
    var tp = new Tuple<int, int>[n]; // Array of n tuples
    tp[i] = Tuple.Create(x, y); // Create a tuple at index i
    int x = tp[i].Item1; // Get the first element of tuple at index i
    int y = tp[i].Item2; // Get the second element of tuple at index i
    int n = tp.Length; // Get the size of the array
    tp.Sort(); // Sort the array of tuples
    tp.Reverse(); // Reverse the array of tuples
    tp.RemoveAll(t => t.Item1 == x); // Remove all tuples with first element equal to x
    // traverse all
    foreach (var t in tp) {
        Console.WriteLine(t.Item1 + " " + t.Item2);
    }

// List of tuples:
    var tp = new List<(int, int)>(); // List of tuples
    var tp = new List<Tuple<int, int>>(); // List of tuples
    tp.Add(Tuple.Create(x, y)); // Add a tuple to the list
    tp.RemoveAt(i); // Remove tuple at index i
    int x = tp[i].Item1; // Get the first element of tuple at index i
    int y = tp[i].Item2; // Get the second element of tuple at index i
    int n = tp.Count; // Get the size of the list
    tp.Sort(); // Sort the list of tuples
    tp.Reverse(); // Reverse the list of tuples
    tp.RemoveAll(t => t.Item1 == x); // Remove all tuples with first element equal to x
    // traverse all
    foreach (var t in tp) {
        Console.WriteLine(t.Item1 + " " + t.Item2);
    }
