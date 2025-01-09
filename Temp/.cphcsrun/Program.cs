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