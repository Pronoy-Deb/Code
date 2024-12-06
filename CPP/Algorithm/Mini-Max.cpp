// Complexity: O(b^d) //b = branching factor, d = depth of the tree

int minimax(int dep, int nd, bool mx, int hit, auto &score) {
	if (dep == hit) return score[nd];
	if (mx) return max(minimax(dep + 1, nd << 1, false, hit, score), minimax(dep + 1, nd << 1 | 1, false, hit, score));
	return min(minimax(dep + 1, nd << 1, true, hit, score), minimax(dep + 1, nd << 1 | 1, true, hit, score));
}

// Operation:
    vector<int> score = {3, 5, 2, 9, 12, 5, 23, 23};
    int n = score.size(); // "score" size must be a power of 2
	cout << minimax(0, 0, true, log2(n), score);