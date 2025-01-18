using System;
using System.Linq.Expressions;
using System.Reflection;

class DebugUtils
{
    // Function to print variable names and values
    public static void ck<T>(Expression<Func<T>> expression)
    {
        var body = (MemberExpression)expression.Body;
        string variableName = body.Member.Name;

        // Get the value of the variable
        T value = expression.Compile().Invoke();

        // Print the variable name and value to the error stream
        Console.Error.WriteLine($"{variableName}: {value}");
    }

    public static void ck<T1, T2>(Expression<Func<T1>> expression1, Expression<Func<T2>> expression2)
    {
        var body1 = (MemberExpression)expression1.Body;
        var body2 = (MemberExpression)expression2.Body;

        string variableName1 = body1.Member.Name;
        string variableName2 = body2.Member.Name;

        T1 value1 = expression1.Compile().Invoke();
        T2 value2 = expression2.Compile().Invoke();

        // Print the variable names and values to the error stream
        Console.Error.WriteLine($"{variableName1}: {value1}, {variableName2}: {value2}");
    }
}

class Program
{
    static void Main()
    {
        int tc = 5;
        var ar = new[] { 1, 2, 3 };

        // Use ck to print variable names and values
        DebugUtils.ck(() => tc, () => ar);
    }
}
