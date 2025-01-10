// Inclusions:
    using System.Collections;

// Operations:
    var sk = new Stack();
    sk.Push(num); // pushes a number
    sk.Push(str); // pushes a string
    int n = sk.Count; // gets the stack size
    object obj = sk.Pop(); // pops an element
    sk.Clear(); // clears the stack
    sk.Peek(); // topmost element of the stack
    sk.Contains(x); // checks the availability of x
    // Traversing:
    foreach (var i in sk) {
        Console.WriteLine(i);
    }
