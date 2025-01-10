// Inclusion:
    using System.Collections;

// Opeations:
    var q = new Queue();
    q.Enqueue(num); // Adds an item to the end of the Queue
    int n = q.Count; // Returns the number of items in the Queue
    object obj = q.Dequeue(); // Removes and returns the object at the beginning of the Queue
    q.Clear(); // Removes all items from the Queue
    q.Peek(); // Returns the object at the beginning of the Queue without removing it
    bool contains = q.Contains(x); // Checks if the Queue contains the object x
    // Traversing:
    foreach (var i in q) {
        Console.WriteLine(i);
    }