template <typename T>
class segtree {
public:
// Merge, modify
    T merge(T a, T b) {
        return max(a, b);
    }

    int size, n;
    T id;
    vector<T> tree;

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < int(a.size())) tree[x] = a[lx];
            else tree[x] = id;
            return;
        }
        int mid = lx + (rx - lx) / 2;
        build(a, x * 2 + 1, lx, mid);
        build(a, x * 2 + 2, mid, rx);
        tree[x] = merge(tree[x * 2 + 1], tree[x * 2 + 2]);
    }

    void build(vector<T> &a) {
        build(a, 0, 0, size);
    }

    segtree(int n, T id) : n(n), id(id) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, id);
    }

    void modify(int i, T v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] -= v;
            return;
        }
        int mid = lx + (rx - lx) / 2;
        if (i < mid) {
            modify(i, v, 2 * x + 1, lx, mid);
        }
        else {
            modify(i, v, 2 * x + 2, mid, rx);
        }
        tree[x] = merge(tree[x * 2 + 1], tree[x * 2 + 2]);
    }

    void modify(int i, T v) {
        modify(i, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        if (lx >= l && rx <= r) return tree[x];
        int mid = lx + (rx - lx) / 2;
        if (mid >= r) return query(l, r, 2 * x + 1, lx, mid);
        if (mid <= l) return query(l, r, 2 * x + 2, mid, rx);
        T left = query(l, r, 2 * x + 1, lx, mid);
        T right = query(l, r, 2 * x + 2, mid, rx);
        return merge(left, right);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }

    int find_geq(int r, int x, int lx, int rx) {
        if (tree[x] < r) return -1;
        if (lx + 1 == rx) return lx;
        int mid = lx + (rx - lx) / 2;
        if (tree[2 * x + 1] >= r) return find_geq(r, 2 * x + 1, lx, mid);
        return find_geq(r, 2 * x + 2, mid, rx);
    }

    int find_geq(int r) {
        return find(r, 0, 0, size);
    }
};
