// Complexity: O(log(n)) for each operation.
// taken from: https://www.programiz.com/dsa/binary-search-tree

struct node {
    int key; struct node *left, *right;
};
// Create a node
struct node *newNode(int item) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp->key = item; tmp->left = tmp->right = NULL;
    return tmp;
}
// Inorder Traversal
void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " -> ";
        inorder(root->right);
    }
}
// Insert a node
struct node *insert(struct node *node, int key) {
    // Return a new node if the tree is empty
    if (node == NULL) return newNode(key);
    // Traverse to the right place and insert the node
    if (key < node->key) node->left = insert(node->left, key);
    else node->right = insert(node->right, key);
    return node;
}
// Find the inorder successor
struct node *minValueNode(struct node *node) {
    struct node *current = node;
    // Find the leftmost leaf
    while (current && current->left != NULL)
    return current = current->left;
}
// Deleting a node
struct node *deleteNode(struct node *root, int key) {
    // Return if the tree is empty
    if (root == NULL) return root;
    // Find the node to be deleted
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        // If the node is with only one child or no child
        if (root->left == NULL) {
            struct node *tmp = root->right;
            free(root); return tmp;
        }
        else if (root->right == NULL) {
            struct node *tmp = root->left;
            free(root); return tmp;
        }
        // If the node has two children
        struct node *tmp = minValueNode(root->right);
        // Place the inorder successor in position of the node to be deleted
        root->key = tmp->key;
        // Delete the inorder successor
        root->right = deleteNode(root->right, tmp->key);
    }
    return root;
}

// Operation:
    struct node *root = NULL;
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 14);
    root = insert(root, 4);

    cout << "Inorder traversal: ";
    inorder(root);

    cout << "\nAfter deleting 10\n";
    root = deleteNode(root, 10);
    cout << "Inorder traversal: ";
    inorder(root);

// BST using STL:
//the code returns a BST which will create if we add the values one by one
//here nodes are indicated by values and every node must be distinct

// Operation:
	cin >> n >> k; //root of the tree
	set<int> st; map<int, int> l, r; // l contains the left child of the node, r contains right child of the node
	st.insert(k);
	for(i = 1; i < n; ++i) {
		cin >> k;
		auto it = st.upper_bound(k);
		if(it != st.end() && l.find(*it) == l.end()) l[*it] = k;
		else --it, r[*it] = k;
		st.insert(k);
	}
	for(i = 1; i <= n; ++i) cout << l[i] << ' ' << r[i] << '\n';