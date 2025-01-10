using System;

class Program {
    static void test(int tc) {
        var vals = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int n = vals[0];
        var ar = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

        Console.WriteLine();
    }

    const int M = 1000000007;
    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool b) { Console.WriteLine(b? "YES" : "NO"); }
}