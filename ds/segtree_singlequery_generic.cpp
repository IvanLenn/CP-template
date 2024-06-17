template <typename T>
class segtree {
public:
    T merge(T a, T b) {
        return a + b;
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
        tree[x] = id;
    }
 
    void build(vector<T> &a) {
        build(a, 0, 0, size);
    }
 
    segtree(int n, T id) : n(n), id(id) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, id);
    }
 
    void modify(int l, int r, T v, int x, int lx, int rx) {
        if (lx >= l && rx <= r) {
            tree[x] = merge(tree[x], v);
            return;
        }
        int mid = lx + (rx - lx) / 2;
        if (mid > l) modify(l, r, v, 2 * x + 1, lx, mid);
        if (mid < r) modify(l, r, v, 2 * x + 2, mid, rx);
    }

    void modify(int l, int r, T v) {
        modify(l, r, v, 0, 0, size);
    }

    T query(int i, int x, int lx, int rx) {
        if (lx + 1 == rx) return tree[x];
        int mid = lx + (rx - lx) / 2;
        if (mid > i) return merge(tree[x], query(i, x * 2 + 1, lx, mid));
        return merge(tree[x], query(i, 2 * x + 2, mid, rx));
    }

    T query(int i) {
        return query(i, 0, 0, size);
    }
};
