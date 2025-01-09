// Problem 1: https://codeforces.com/problemset/problem/1999/C
// Solution:
using System;

class Program {
    static void test(int tc) {
        long[] ar = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
        long n = ar[0], s = ar[1], m = ar[2], pre = 0;
        bool ok = false;
        while (n-- > 0) {
            int[] pair = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            int l = pair[0], r = pair[1];
            if (l - pre >= s) ok = true;
            pre = r;
        }
        ok |= (m - pre >= s);
        ps(ok);
    }

    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool condition) { Console.WriteLine(condition ? "YES" : "NO"); }
}

// Problem 2: https://codeforces.com/problemset/problem/1996/B
// Solution:

using System;
class Program {
    static void test(int tc) {
        // int n = int.Parse(Console.ReadLine());
        int[] num = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int n = num[0], k = num[1];
        char[,] ar = new char[n, n];
        for (int i = 0; i < n; ++i) {
            string s = Console.ReadLine();
            for (int j = 0; j < n; ++j) ar[i, j] = s[j];
        }
        char[,] ans = new char[n / k, n / k];
        for (int i = 0, m = 0; i < n; i += k, ++m) {
            for (int j = 0, l = 0; j < n; j += k, ++l) ans[m, l] = ar[i, j];
        }
        for (int i = 0; i < n / k; ++i) {
            for (int j = 0; j < n / k; ++j) Console.Write(ans[i, j]);
            Console.WriteLine();
        }
    }

    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool b) { Console.WriteLine(b ? "YES" : "NO"); }
}

// Problem 3: https://codeforces.com/problemset/problem/1914/B
// Solution:
using System;
class Program {
    static void test(int tc) {
        // int n = int.Parse(Console.ReadLine());
        int[] ar = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int n = ar[0], k = ar[1];
        int l = n - k;
        for (int i = l; i <= n; ++i) Console.Write(i + " ");
        for (int i = l - 1; i > 0; --i) Console.Write(i + " ");
        Console.WriteLine();
    }

    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool b) { Console.WriteLine(b ? "YES" : "NO"); }
}

// Problem 4: https://codeforces.com/problemset/problem/1993/A
// Solution:
using System;
class Program {
    static void test(int tc) {
        int n = int.Parse(Console.ReadLine());
        // int[] ar = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        string s = Console.ReadLine();
        int[] ar = new int[4];
        foreach (char c in s) {
            if (c != '?') ++ar[c - 'A'];
        }
        int tot = 0;
        foreach (int e in ar) tot += Math.Min(n, e);
        Console.Write(tot);
        Console.WriteLine();
    }

    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool b) { Console.WriteLine(b ? "YES" : "NO"); }
}

// Problem 5: https://codeforces.com/problemset/problem/1999/B
// Solution:
using System;

class Program {
    static void test(int tc) {
        // int n = int.Parse(Console.ReadLine());
        int[] ar = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int a = ar[0], b = ar[1], c = ar[2], d = ar[3];
        int sunnet = 0, slavic = 0, sun = 0, sla = 0;
        if (a > c) sun++; else if (a < c) sla++;
        if (b > d) sun++; else if (b < d) sla++;
        if (sun > sla) sunnet += 2; else if (sun < sla) slavic += 2;
        sun = sla = 0;
        if (a > d) sun++; else if (a < d) sla++;
        if (b > c) sun++; else if (b < c) sla++;
        if (sun > sla) sunnet += 2; else if (sun < sla) slavic += 2;
        Console.Write(sunnet);
        Console.WriteLine();
    }

    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool b) { Console.WriteLine(b ? "YES" : "NO"); }
}

// Problem 6:
// Solution:
