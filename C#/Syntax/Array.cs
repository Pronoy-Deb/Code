Declaring a 1D array:
    var ar = new int[n]; // Array of size n

Declaring a 2D array:
    var ar = new int[m, n]; // Array of size m x n
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