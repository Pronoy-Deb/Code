Declaring a 1D array:
    int[] ar = new int[n]; // Array of size n
To use like vectors of c++:
    List<int> ar = new List<int>(n); // List of size n
    ar.Add(x); // Add element x to the end of the list
    ar.RemoveAt(i); // Remove element at index i
    int x = ar[i]; // Get element at index i
    int n = ar.Count; // Get the size of the list
    ar.Clear(); // Remove all elements from the list
    ar.Sort(); // Sort the list in ascending order
    ar.Reverse(); // Reverse the list
    ar.RemoveAll(x => x == y); // Remove all elements equal to y from the list
    // traverse all
    foreach (int i in ar) {
        Console.WriteLine(i);
    }

To use like vectors of vectors:
    List<List<int>> ar = new List<List<int>>(n); // List of size n, where each inner list is also a list
    ar[i].Add(x); // Add element x to the end of the i-th inner list
    ar[i].RemoveAt(j); // Remove element at index j from the i-th inner list
    int x = ar[i][j]; // Get element at index j of the i-th inner list
    int n = ar[i].Count; // Get the size of the i-th inner list
    ar[i].Clear(); // Remove all elements from the i-th inner list
    ar[i].Sort(); // Sort the i-th inner list in ascending order
    ar[i].Reverse(); // Reverse the i-th inner list
    ar[i].RemoveAll(x => x == y); // Remove all elements equal to y from the i-th inner list
    // traverse all
    foreach (List<int> sublist in ar) {
        foreach (int i in sublist) {
            Console.WriteLine(i);
        }
    }

Declaring a 2D array:
    int[,] ar = new int[m, n]; // Array of size m x n
    ar[i, j] = x; // Set element at position (i, j) to x
    int x = ar[i, j]; // Get element at position (i, j)
    int m = ar.GetLength(0); // Get the number of rows
    int n = ar.GetLength(1); // Get the number of columns
    ar.Clear(); // Remove all elements from the array
    ar.Sort(); // Sort the array in ascending order
    ar.Reverse(); // Reverse the array
    ar.RemoveAll(x => x == y); // Remove all elements equal to y from the array
    // traverse all
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Console.WriteLine(ar[i, j]);
        }
    }

Finding min, max, sum:
    using System.Linq;
    int min = ar.Min();
    int max = ar.Max();
    int sum = ar.Sum();