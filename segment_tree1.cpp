struct segment_tree {
    struct node {
        ll sum;
        ll set;
    };

    vector<node> tree;
    int size;
    ll NO_OPERATION = LLONG_MIN;
    ll NEUTRAL_ELEMENT = 0;

    segment_tree(int _size) {
        size = _size;
        tree.assign(4 * size, { NEUTRAL_ELEMENT, NO_OPERATION });
    }

    void push(int x, int lx, int rx) {
        if (tree[x].set == NO_OPERATION) {
            return;
        }

        tree[x].sum = (rx - lx) * tree[x].set;
        if (rx - lx > 1) {
            tree[2 * x + 1].set = tree[2 * x + 2].set = tree[x].set;
        }

        tree[x].set = NO_OPERATION;
    }

    void set(int l, int r, ll v, int x, int lx, int rx) {
        push(x, lx, rx);
        if (lx >= r || rx <= l) {
            return;
        }
        if (lx >= l && rx <= r) {
            tree[x].set = v;
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
    }

    void set(int l, int r, ll v) {
        set(l, r, v, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (lx >= r || rx <= l) {
            return NEUTRAL_ELEMENT;
        }
        if (lx >= l && rx <= r) {
            return tree[x].sum;
        }
        int m = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, m) + sum(l, r, 2 * x + 2, m, rx);
    }

    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};
