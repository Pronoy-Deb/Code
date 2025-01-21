using System; using System.Collections; using System.Linq.Expressions;

class Program {
    static void test(int tc) {
        var vals = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int n = vals[0];
        var ar = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        int j = n - 1;
        while (j > 0 && ar[j - 1] <= ar[j]) --j;
        for (int i = 0; i < j - 1; ++i) {
            int a = Math.Min(ar[i], ar[i + 1]);
            ar[i] -= a; ar[i + 1] -= a;
            if (ar[i] > 0) {
                ps(false); return;
            }
        }
        ps(j == 0 || ar[j - 1] <= ar[j]);
        // Console.WriteLine();
    }

    const int M = 1000000007;
    static void Main(string[] args) {
        int tc = 0, tt = 1;
        tt = int.Parse(Console.ReadLine());
        while (tc++ < tt) test(tc);
    }
    static void pe<T>(IEnumerable<T> array) { Console.WriteLine(string.Join(" ", array)); }
    static void ps(bool b) { Console.WriteLine(b? "YES" : "NO"); }
    static void ck<T>(Expression<Func<T>> expression) {
        var body = (MemberExpression)expression.Body;
        string variableName = body.Member.Name;
        T value = expression.Compile().Invoke();
        Console.Error.Write($"{variableName} = ");
        if (value is IEnumerable enu && value is not string) {
            Console.Error.WriteLine($"[{string.Join(", ", enu.Cast<object>())}]");
        }
        else if (value is IDictionary dictionary) {
            foreach (DictionaryEntry ent in dictionary)
                Console.Error.WriteLine($"{ent.Key}: {ent.Value}");
        }
        else Console.Error.WriteLine(value);
    }
}