// insert, search, delete operation in O(k * logn)

const int k = 2;
struct Node {
	int point[k]; Node *left, *right;
};
struct Node* newNode(int arr[]) {
	struct Node* temp = new Node;
	for (int i = 0; i < k; ++i) temp->point[i] = arr[i];
	temp->left = temp->right = NULL; return temp;
}
Node *ins(Node *root, int point[], unsigned dep = 0) {
	if (root == NULL) return newNode(point); unsigned cd = dep % k;
	if (point[cd] < (root->point[cd])) root->left = ins(root->left, point, dep + 1);
	else root->right = ins(root->right, point, dep + 1);
	return root;
}
inline Node *minNode(Node *x, Node *y, Node *z, int d) {
	Node *res = x;
	if (y != NULL && y->point[d] < res->point[d]) res = y;
	if (z != NULL && z->point[d] < res->point[d]) res = z;
	return res;
}
Node *mn(Node* root, int d, unsigned dep = 0) {
	if (root == NULL) return NULL; unsigned cd = dep % k;
	if (cd == d) {
		if (root->left == NULL) return root;
		return mn(root->left, d, dep + 1);
	}
	return minNode(root, mn(root->left, d, dep + 1), mn(root->right, d, dep + 1), d);
}
bool same(int point1[], int point2[]) {
	for (int i = 0; i < k; ++i) {
		if (point1[i] != point2[i]) return false;
	}
	return true;
}
void copy(int p1[], int p2[]) {
	for (int i = 0; i < k; ++i) p1[i] = p2[i];
}
bool find(Node* root, int point[], unsigned dep = 0) {
    if (root == NULL) return false;
    if (same(root->point, point)) return true;
    unsigned cd = dep % k;
    if (point[cd] < root->point[cd]) return find(root->left, point, dep + 1);
    return find(root->right, point, dep + 1);
}
Node *rem(Node *root, int point[], int dep = 0) {
	if (root == NULL) return NULL; int cd = dep % k;
	if (same(root->point, point)) {
		if (root->right != NULL) {
			Node *min = mn(root->right, cd);
			copy(root->point, min->point);
			root->right = rem(root->right, min->point, dep+1);
		}
		else if (root->left != NULL) {
			Node *min = mn(root->left, cd);
			copy(root->point, min->point);
			root->right = rem(root->left, min->point, dep+1);
		}
		else { delete root; return NULL; } return root;
	}
	if (point[cd] < root->point[cd]) root->left = rem(root->left, point, dep + 1);
	else root->right = rem(root->right, point, dep + 1);
	return root;
}

// Operation:
	struct Node *rt = NULL;
	int n; cin >> n; int ar[n][k];
	for (int i = 0; i < n; ++i) {
        cin >> ar[i][0] >> ar[i][1]; rt = ins(rt, ar[i]);
    }
	rt = rem(rt, ar[0]);
	cout << rt->point[0] << ' ' << rt->point[1] << '\n';
	int pnt[] = {5, 25}; // Finding the point:
	cout << boolalpha << find(rt, pnt) << '\n';
	// Minimum of 0'th dimension and 1'th dimension:
	cout << mn(rt, 0)->point[0] << ' ' << mn(rt, 1)->point[1] << '\n';

https://www.spoj.com/problems/GANNHAT/

const int k = 2; // Dimension
struct point {
    long long p[k];
    bool operator!=(const point &a) const {
        bool ok = 1;
        for (int i = 0; i < k; ++i) ok &= (p[i] == a.p[i]);
        return !ok;
    }
};
struct kd_node {
    int axis, value; point p; kd_node *left, *right;
};
struct cmp {
    int axis;
    cmp(int x) : axis(x) {}
    bool operator()(const point &a, const point &b) const {
        return a.p[axis] < b.p[axis];
    }
};
typedef kd_node *node_ptr;
node_ptr root; point ar[N]; int n;
long long manhattan(point a, point b) {
    long long res = 0;
    for (int i = 0; i < k; ++i) res += abs(a.p[i] - b.p[i]);
        // res += (a.p[i] - b.p[i]) * (a.p[i] - b.p[i]);
    return res;
}
void make(node_ptr &node = root, int from = 0, int to = n - 1, int axis = 0) {
    if (from > to) { node = NULL; return; }
    node = new kd_node();
    if (from == to) {
        node->p = ar[from]; node->left = NULL;
        node->right = NULL; return;
    }
    int mid = (from + to) >> 1;
    nth_element(ar + from, ar + mid, ar + to + 1, cmp(axis));
    node->value = ar[mid].p[axis]; node->axis = axis;
    make(node->left, from, mid, (axis + 1) % k);
    make(node->right, mid + 1, to, (axis + 1) % k);
}
long long get(node_ptr node, point q) {
	long long ans = M * M; if (node == NULL) return ans;
    if (node->left == NULL && node->right == NULL) {
        if (q != node->p) ans = min(ans, manhattan(node->p, q)); // Change accordingly
        return ans;
    }
    if (q.p[node->axis] <= node->value) {
        ans = min(ans, get(node->left, q));
        if (q.p[node->axis] + ans >= node->value) ans = min(ans, get(node->right, q));
    }
    else {
        ans = min(ans, get(node->right, q));
        if (q.p[node->axis] - ans <= node->value) ans = min(ans, get(node->left, q));
    }
	return ans;
}

// Operation:
    cin >> n; point pts[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) cin >> ar[i].p[j];
        pts[i] = ar[i];
    }
    make();
    for (int i = 0; i < n; ++i) cout << get(root, pts[i]) << '\n';