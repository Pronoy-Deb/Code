# Complexity: O(2^n)

def gen(s, open, close, com):
    if open == 0 and close == 0: com.append(s); return
    if open > 0: gen(s + '(', open - 1, close, com)
    if close > 0 and open < close: gen(s + ')', open, close - 1, com)

# Example of calling the function
empty_str = ""
n = 3  # Example with 3 pairs of parentheses
empty_vec = []
gen(empty_str, n, n, empty_vec)
for combination in empty_vec:
    print(combination)