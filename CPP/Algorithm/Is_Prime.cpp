// Complexity: O(k * log(n))
// Fermat Method of Primality Test:

mt19937 ran(chrono::steady_clock::now().time_since_epoch().count());
long long bex(long long a, long long n, long long p) {
	long long res = 1; a %= p;
	while (n) {
		if (n & 1) res = (res * a) % p;
		n >>= 1; a = (a * a) % p;
	}
	return res;
}
bool pri(long long n, int k = 10) {
    if (n == 2 || n == 3) return true;
	if (n < 2 || !(n % 2) || !(n % 3)) return false;
    while (k--) {
        long long a = 2 + ran() % (n - 4);
        if (gcd(n, a) != 1 || bex(a, n - 1, n) != 1) return false;
	}
	return true;
}

// Solovay-Strassen method of Primality Test:

mt19937 ran(chrono::steady_clock::now().time_since_epoch().count());
long long bex(long long a, long long n, long long p) {
	long long res = 1; a %= p;
	while (n) {
		if (n & 1) res = (res * a) % p;
		n >>= 1; a = (a * a) % p;
	}
	return res;
}
long long jaco(long long a, long long n) {
	if (!a) return 0;
	long long ans = 1;
	if (a < 0) {
		a = -a; if (n % 4 == 3) ans = -ans;
	}
	if (a == 1) return ans;
	while (a) {
		if (a < 0) {
			a = -a;
			if (n % 4 == 3) ans = -ans;
		}
		while (~a & 1) {
			a >>= 1;
			if (n % 8 == 3 || n % 8 == 5) ans = -ans;
		}
		swap(a, n);
		if (a % 4 == 3 && n % 4 == 3) ans = -ans;
		a %= n; if (a > (n >> 1)) a = a - n;
	}
	if (n == 1) return ans;
	return 0;
}
bool pri(long long p, int k = 50) {
	if (p < 2) return false;
	if (p != 2 && (~p & 1)) return false;
	while (k--) {
		long long a = ran() % (p - 1) + 1, jb = (p + jaco(a, p)) % p, m = bex(a, (p - 1) >> 1, p);
		if (!jb || m != jb) return false;
	}
	return true;
}

// Complexity: O(sqrt(n))

bool pri(long long n) {
	if (n == 2 || n == 3) return true;
	if (n < 2 || !(n % 2) || !(n % 3)) return false;
	for (long long i = 5; i * i <= n; i += 6) {
		if (!(n % i) || !(n % (i + 2))) return false;
	}
	return true;
}

// OR,

bool pri(long long n) {
    if (n == 2) return true;
    if (n < 2 or ~n & 1) return false;
    for (long long i = 3; i * i <= n; i += 2) {
        if (!(n % i)) return false;
    }
    return true;
}