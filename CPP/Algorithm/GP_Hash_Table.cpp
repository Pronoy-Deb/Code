https://cses.fi/problemset/task/1640

// #include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int rnd = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ rnd; }
};
gp_hash_table<long long, long long, chash> tab;

// OR, For Pairs-

struct chash {
    int operator()(pair<int, int> x) const { return x.first* 31 + x.second; }
};
gp_hash_table<pair<int, int>, int, chash> tab;

// OR, For Pairs-

struct chash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(pair<uint64_t, uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM) ^ (splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

// OR, Usual Hashing-

struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<long long, long long, chash> tab;

// Operation:
    cin >> n >> k;
    for (i = 0; i < n; ++i) {
        if (tab[k - ar[i]]) {
            cout << tab[k - ar[i]] << ' ' << i + 1 << '\n';
            return;
        }
        tab[ar[i]] = i + 1;
    }
    cout << "IMPOSSIBLE\n";

// For usual unordered_map:

struct chash {
	// any random-ish large odd number will do
	const uint64_t C = uint64_t(2e18 * PI) + 71;
	// random 32-bit number
	const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x ^ RANDOM) * C);
	}
};
template <class K, class V> using cmap = unordered_map<K, V, chash>;
// example usage: cmap<int, int>

// gp_hash_table that supports resize() function:

template <class K, class V>
using ht = gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<>, true>>;

// Operation:
	ht<int, null_type> g;
	g.resize(5);
	cout << g.get_actual_size() << '\n';  // 8
	cout << g.size() << '\n';             // 0
// also,
    ht<int, null_type> g({}, {}, {}, {}, {1 << 16}); // initialize with certain capacity, must be power of 2