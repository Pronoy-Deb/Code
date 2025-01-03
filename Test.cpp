#include<bits/stdc++.h>
using namespace std;

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

// Driver program to test above functions
int main()
{
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
	return 0;
}
