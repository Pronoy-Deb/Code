# Complexity: O(n)
# Note: Repd nber is a nber n which has all the ds in its representation in base b equal.

def rd(n, b):
	p = -1
	while n:
		d = n % b; n //= b
		if p != -1 and d != p: return False
		p = d
	return True