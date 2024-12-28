// Note: 0-based indexing, Range is [L, R), L is inclusive, R is exclusive.
https://codeforces.com/gym/103997/problem/A

namespace allocation { // Array allocation.
template <class T, int SZ>
struct array {
    T v[SZ], *top; array() : top(v) {}
    T *alloc(const T &val = T()) { return &(*top++ = val); }
    void dealloc(T *p) {}
};
template <class T, int SZ> // Stack-based array allocation.
struct stack {
    T v[SZ], *spot[SZ], **top;
    stack() {
        for (int i = 0; i < SZ; ++i) spot[i] = v + i;
        top = spot + SZ;
    }
    T *alloc(const T &val = T()) { return &(**--top = val); }
    void dealloc(T *p) { *top++ = p; }
};
}
namespace splay { // Splay tree.
template <class T>
struct nd {
    T *f, *c[2]; int size;
    nd() { f = c[0] = c[1] = nullptr; size = 1; }
    void push_down() {}
    void update() {
        size = 1;
        for (int t = 0; t < 2; ++t) if (c[t]) size += c[t]->size;
    }
};
template <class T> // Abstract reversible node struct.
struct reversible_node : nd<T> {
    int r; reversible_node() : nd<T>() { r = 0; }
    void push_down() {
        nd<T>::push_down();
        if (r) {
            for (int t = 0; t < 2; ++t) if (nd<T>::c[t]) nd<T>::c[t]->reverse();
            r = 0;
        }
    }
    void update() { nd<T>::update(); }
    void reverse() { // Reverse the range of this node.
        swap(nd<T>::c[0], nd<T>::c[1]); r ^= 1;
    }
};
template <class T, int SZ, class alloc = allocation::array<T, SZ>>
struct tree {
    alloc pool; T *root; // Get a new node from the pool.
    T *nnd(const T &val = T()) { return pool.alloc(val); }
    tree() {
        root = nnd(), root->c[1] = nnd(), root->size = 2;
        root->c[1]->f = root;
    }
    // Helper function to rotate_right node.
    void rotate_right(T *n) {
        int v = n->f->c[0] == n; T *p = n->f, *m = n->c[v];
        if (p->f) p->f->c[p->f->c[1] == p] = n;
        n->f = p->f, n->c[v] = p; p->f = n, p->c[v ^ 1] = m;
        if (m) m->f = p; p->update(), n->update();
    }
    // Splay n so that it is under s (or to root if s is null).
    void splay(T *n, T *s = nullptr) {
        while (n->f != s) {
            T *m = n->f, *l = m->f;
            if (l == s) rotate_right(n);
            else if ((l->c[0] == m) == (m->c[0] == n)) rotate_right(m), rotate_right(n);
            else rotate_right(n), rotate_right(n);
        }
        if (!s) root = n;
    }
    int size() { return root->size - 2; } // Get the size of the tree.
    int walk(T *n, int &v, int &pos) { // Helper function to walk down the tree.
        n->push_down(); int s = n->c[0] ? n->c[0]->size : 0;
        (v = s < pos) && (pos -= s + 1); return s;
    }
    // Insert node n to position pos.
    void insert(int pos, T *n) {
        T *c = root; int v; ++pos;
        while (walk(c, v, pos), c->c[v] && (c = c->c[v]));
        c->c[v] = n, n->f = c, splay(n);
    }
    // Find the node at position pos. If sp is true, splay it.
    T *find(int pos, int sp = true) {
		T *c = root; int v; ++pos;
        while ((pos < walk(c, v, pos) || v) && (c = c->c[v]));
        if (sp) splay(c); return c;
    }
    // Find the range [L, R) on the splay tree.
    T *range(int L, int R) {
        T *r = find(R), *l = find(L - 1, false); splay(l, r);
        if (l->c[1]) l->c[1]->push_down(); return l->c[1];
    }
    // Insert nn of size nn_size to position pos.
    void insert_range(T **nn, int nn_size, int pos) {
        T *r = find(pos), *l = find(pos - 1, false), *c = l; splay(l, r);
        for (int i = 0; i < nn_size; ++i) c->c[1] = nn[i], nn[i]->f = c, c = nn[i];
        for (int i = nn_size - 1; i >= 0; --i) nn[i]->update();
        l->update(), r->update(), splay(nn[nn_size - 1]);
    }
    void rotate(int L, int R, int k) {
        ++L; k %= (R - L + 1);
        if (k > 0) {
            // swap [L - 1, R - k) and [R - k, R)
            T *right = range(R - k, R);
            right->f->c[1] = nullptr, right->f->update(), right->f->f->update(), right->f = nullptr;
            insert(L - 1, right);
        }
    }
    // Helper function to dealloc a subtree.
    void dealloc(T *n) {
        if (!n) return; dealloc(n->c[0]); dealloc(n->c[1]);
        pool.dealloc(n);
    }
    // Remove from position [L, R).
    void erase(int L, int R) {
        T *n = range(L, R);
        n->f->c[1] = nullptr, n->f->update(), n->f->f->update(), n->f = nullptr; dealloc(n);
    }
};
}
// TODO:
// 1. Define a node inheriting from splay::nd<nd> or splay::reversible_node<nd>.
// 2. Add the values you want to use.
// 3. Overload the constructor, push_down, update, (potentially) reverse.
// (Do not forget to call the base method.)
// 4. Add whatever operations you want.
// 5. Define a tree with splay::tree<nd, N, allocation::stack<nd, N>> t;
// 6. Profit.
struct nd : splay::reversible_node<nd> {
    long long val, mn, label_add;
    nd(long long v = 0) : splay::reversible_node<nd>(), val(v) { mn = label_add = 0; }
    void add(long long v) { // Add v to the subtree.
        val += v; mn += v; label_add += v;
    }
    void push_down() {
        splay::reversible_node<nd>::push_down();
        for (int t = 0; t < 2; ++t) if (c[t]) c[t]->add(label_add);
        label_add = 0;
    }
    void update() {
        splay::reversible_node<nd>::update(); mn = val;
        for (int t = 0; t < 2; ++t) if (c[t]) mn = min(mn, c[t]->mn);
    }
};
splay::tree<nd, N, allocation::stack<nd, (N << 2)>> t;

// Operation:
	int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int a; cin >> a; t.insert(i, t.nnd(nd(a)));
    }
    int m; cin >> m;
    while (m--) {
        string s; cin >> s;
        if (s == "ADD") {
            int l, r, x; cin >> l >> r >> x;
            t.range(l - 1, r)->add(x);
        } else if (s == "REVERSE") {
            int l, r; cin >> l >> r;
            t.range(l - 1, r)->reverse();
        } else if (s == "REVOLVE") {
            int l, r, k; cin >> l >> r >> k;
            t.rotate(l - 1, r, k);
        } else if (s == "INSERT") {
            int l, x; cin >> l >> x;
            t.insert(l, t.nnd(nd(x)));
        } else if (s == "DELETE") {
            int l; cin >> l; t.erase(l - 1, l);
        } else {
            int l, r; cin >> l >> r;
            cout  << t.range(l - 1, r)->mn << '\n';
        }
    }

// Tutorial URL: http://algorithmtutor.com/Data-Structures/Tree/Splay-Trees/

#include <iostream>

using namespace std;

// data structure that represents a node in the tree
struct Node {
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
};

typedef Node *NodePtr;

// class SplayTree implements the operations in Splay tree
class SplayTree {
private:
	NodePtr root;

	void preOrderHelper(NodePtr node) {
		if (node != nullptr) {
			cout<<node->data<<" ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(NodePtr node) {
		if (node != nullptr) {
			inOrderHelper(node->left);
			cout<<node->data<<" ";
			inOrderHelper(node->right);
		}
	}

	void postOrderHelper(NodePtr node) {
		if (node != nullptr) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout<<node->data<<" ";
		}
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == nullptr || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr x = nullptr;
		NodePtr t, s;
		while (node != nullptr){
			if (node->data == key) {
				x = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (x == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		}
		split(x, s, t); // split the tree
		if (s->left){ // remove x
			s->left->parent = nullptr;
		}
		root = join(s->left, t);
		delete(s);
		s = nullptr;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != nullptr) {
		   cout<<indent;
		   if (last) {
		      cout<<"└────";
		      indent += "     ";
		   } else {
		      cout<<"├────";
		      indent += "|    ";
		   }

		   cout<<root->data<<endl;

		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// splaying
	void splay(NodePtr x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig rotation
					rightRotate(x->parent);
				} else {
					// zag rotation
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig rotation
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag rotation
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag rotation
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				// zag-zig rotation
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

	// joins two trees s and t
	NodePtr join(NodePtr s, NodePtr t){
		if (!s) {
			return t;
		}

		if (!t) {
			return s;
		}
		NodePtr x = maximum(s);
		splay(x);
		x->right = t;
		t->parent = x;
		return x;
	}

	// splits the tree into s and t
	void split(NodePtr &x, NodePtr &s, NodePtr &t) {
		splay(x);
		if (x->right) {
			t = x->right;
			t->parent = nullptr;
		} else {
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	}

public:
	SplayTree() {
		root = nullptr;
	}

	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder() {
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder() {
		inOrderHelper(this->root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder() {
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	NodePtr searchTree(int k) {
		NodePtr x = searchTreeHelper(this->root, k);
		if (x) {
			splay(x);
		}
		return x;
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != nullptr) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the
		// left subtree
		if (x->left != nullptr) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// insert the key to the tree in its appropriate position
	void insert(int key) {
		// normal BST insert
		NodePtr node = new Node;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->data = key;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		// splay the node
		splay(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	// delete the node from the tree
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void prettyPrint() {
		printHelper(this->root, "", true);
	}

};

int main() {
	SplayTree bst;
	bst.insert(33);
	bst.insert(44);
	bst.insert(67);
	bst.insert(5);
	bst.insert(89);
	bst.insert(41);
	bst.insert(98);
	bst.insert(1);
	bst.prettyPrint();
	bst.searchTree(33);
	bst.searchTree(44);
	bst.prettyPrint();
	bst.deleteNode(89);
	bst.deleteNode(67);
	bst.deleteNode(41);
	bst.deleteNode(5);
	bst.prettyPrint();
	bst.deleteNode(98);
	bst.deleteNode(1);
	bst.deleteNode(44);
	bst.deleteNode(33);
	bst.prettyPrint();
	return 0;
}