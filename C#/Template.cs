using System;

class Program {
    static void test(int tc) {
        long n = long.Parse(Console.ReadLine());
        var ar = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);

    }

    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) {
        Console.WriteLine(string.Join(" ", array));
    }
    static void ps(bool condition) {
        Console.WriteLine(condition ? "YES" : "NO");
    }
}