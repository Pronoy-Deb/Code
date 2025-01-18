// To determine minimum of two numbers:
    Math.Min(a, b);

// For several numbers:
public static int Min(params int[] numbers) {
    if (numbers == null || numbers.Length == 0) {
        throw new ArgumentException("At least one number must be provided");
    }
    int min = numbers[0];
    for (int i = 1; i < numbers.Length; i++) {
        min = Math.Min(min, numbers[i]);
    }
    return min;
}

// Taking the reference of a variable:
    ref var c = ref s[j];