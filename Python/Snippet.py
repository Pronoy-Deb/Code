{
	// Place your snippets for python here. Each snippet is defined under a snippet name and has a prefix, body and
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the
	// same ids are connected.
	// Example:
	"Print to console": {
		"prefix": "te",
		"body": [
			// 		"console.log('$1');",
			// 		"$2"
			"from os import read, write, fstat; from sys import stdin, stdout; from io import BytesIO, IOBase; BS = 8192",
			"class FastIO(IOBase):",
			"\tnl = 0",
			"\tdef __init__(self, file): self._file = file; self._fd = file.fileno(); self.buffer = BytesIO(); self.writable = \"x\" in file.mode or \"r\" not in file.mode; self.write = self.buffer.write if self.writable else None",
			"\tdef read(self):",
			"\t\twhile True:",
            "\t\t\tb = read(self._fd, max(fstat(self._fd).st_size, BS))",
            "\t\t\tif not b: break",
            "\t\t\tptr = self.buffer.tell(); self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)",
			"\t\tself.nl = 0; return self.buffer.read()",
			"\tdef readline(self):",
			"\t\twhile not self.nl: b = read(self._fd, max(fstat(self._fd).st_size, BS)); self.nl = b.count(b\"\\n\") + (not b); ptr = self.buffer.tell(); self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)",
			"\t\tself.nl -= 1; return self.buffer.readline()",
			"\tdef flush(self):",
			"\t\tif self.writable: write(self._fd, self.buffer.getvalue()); self.buffer.truncate(0), self.buffer.seek(0)",
			"class IOWrapper(IOBase):",
			"\tdef __init__(self, file): self.buffer = FastIO(file); self.flush = self.buffer.flush; self.writable = self.buffer.writable; self.write = lambda s: self.buffer.write(s.encode(\"ascii\")); self.read = lambda: self.buffer.read().decode(\"ascii\"); self.readline = lambda: self.buffer.readline().decode(\"ascii\")",
			"stdin, stdout = IOWrapper(stdin), IOWrapper(stdout); input = lambda: stdin.readline().rstrip(\"\\r\\n\")",
			"def ck(*A): from sys import stderr; from inspect import currentframe; stderr.write(\", \".join([f\"{t} = {v}\" for t, v in zip([t for t, v in currentframe().f_back.f_locals.items() if v in A], A)]) + '\\n')",
			"inp = lambda: (c := stdin.readline().split(), int(c[0]) if len(c) == 1 else [int(x) for x in c])[1]",
			"def pn(c, n): [stdout.write(str(c[i]) + ' ') for i in range(n)]; stdout.write('\\n')",
			"def ols(ls): [stdout.write(str(x) + ' ') for x in ls]; stdout.write('\\n')",
			"def ps(b): stdout.write(\"YES\\n\" if b else \"NO\\n\")",
			"def pc(t): stdout.write(\"Case \" + str(t) + \": \")",
			"def out(n): stdout.write(str(n) + '\\n')",
			"M, N = 1000000007, 200005",
			"",
			"def Test(tc):",
			"\tn = inp()",
			"\tls = inp()",
			"\t$0",
			"",
			"if __name__ == \"__main__\":",
			"\tt = tc = 1",
			"\ttc = inp()",
			"\twhile t <= tc: Test(t); t += 1",
		],
	// 	"description": "Log output to console"
	// }
}