mt19937 rnd(41);

struct node {
	int key;
	int priority;
	node* left;
	node* right;
	int size;

	node(int key) : key(key), priority(rnd()), left(nullptr), right(nullptr), size(1) {}
};

int size(node* v) {
	return (v == nullptr ? 0 : v->size);
}

void print(node* root, int d = 0) {
	if (root == nullptr) {
		return;
	}
	print(root->right, d + 1);
	for (int i = 0; i < d; ++i) cout << ' ';
	cout << root->key << "\n";
	print(root->left, d + 1);
}

void update(node* v) {
	if (v == nullptr) {
		return;
	}
	v->size = size(v->left) + 1 + size(v->right);
}

node* merge(node* left, node* right) {
	if (left == nullptr) {
		return right;
	}
	if (right == nullptr) {
		return left;
	}

	if (left->priority > right->priority) {
		left->right = merge(left->right, right);
		update(left);
		return left;
	}
	else {
		right->left = merge(left, right->left);
		update(right);
		return right;
	}
}


pair<node*, node*> split(node* root, int key) {
	if (root == nullptr) {
		return { nullptr, nullptr };
	}
	if (root->key < key) {
		auto sp = split(root->right, key);
		root->right = sp.first;
		update(root);
		return { root, sp.second };
	}
	else {
		auto sp = split(root->left, key);	
		root->left = sp.second;
		update(root);
		return { sp.first, root };
	}
}

tuple<node*, node*, node*> split(node* root, int l, int r) {
	node* left, * mid, * right;
	tie(left, mid) = split(root, l);
	tie(mid, right) = split(mid, r + 1);
	return { left, mid, right };
}

node* merge(node* left, node* mid, node* right) {
	return merge(merge(left, mid), right);
}


void insert(node*& root, node* v) {
	auto [left, right] = split(root, v->key);
	root = merge(left, v, right);
}

void erase(node*& root, int key) {
	auto [left, mid, right] = split(root, key, key);
	root = merge(left, right);
}

int kth_max(node* root, int k) {
	int root_order = size(root->right);
	if (k < root_order) {
		return kth_max(root->right, k);
	}
	else if (k == root_order) {
		return root->key;
	}
	else {
		return kth_max(root->left, k - root_order - 1);
	}
}
