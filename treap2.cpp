mt19937 rnd(41);

struct node {
	int val;
	int priority;
	node* left;
	node* right;
	int size;

	node(int val) : val(val), priority(rnd()), left(nullptr), right(nullptr), size(1) {}
};

ostream& operator<<(ostream& out, node* root) {
	if (root == nullptr)
		return out;
	out << root->left;
	out << root->val << " ";
	out << root->right;
	return out;
}

int size(node* v) {
	return (v == nullptr ? 0 : v->size);
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


pair<node*, node*> split(node* root, int pref) {
	if (root == nullptr) {
		return { nullptr, nullptr };
	}
	int root_pos = size(root->left);
	if (pref <= root_pos) {
		auto sp = split(root->left, pref);
		root->left = sp.second;
		update(root);
		return { sp.first, root };
	}
	else {
		auto sp = split(root->right, pref - root_pos - 1);
		root->right = sp.first;
		update(root);
		return { root, sp.second };
	}
}

tuple<node*, node*, node*> split(node* root, int l, int r) {
	node* left, * mid, * right;
	tie(mid, right) = split(root, r + 1);
	tie(left, mid) = split(mid, l);
	return { left, mid, right };
}

node* merge(node* left, node* mid, node* right) {
	return merge(merge(left, mid), right);
}


void insert(node*& root, int pos, int val) {
	auto [left, right] = split(root, pos);
	root = merge(left, new node(val), right);
}


void push_back(node*& root, int val) {
	root = merge(root, new node(val));
}
