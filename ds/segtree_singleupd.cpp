template<class F>
struct segtree{
    // modify: merge, modify, base case
    int cnt;  // array size
    vector<F> t;

    segtree() {}
    void resize(int n) {
        cnt = n;
        t.resize(2 * n);
    }
    
    inline F merge(F a, F b) {
        return a + b;
    }
    
    void build() {  // build the tree
        for (int i = cnt - 1; i > 0; --i) {
            t[i] = merge(t[i<<1], t[i<<1|1]);
        }
    }
    
    void modify(int p, F value) {  // set value at position p
        p += cnt;
        t[p] = value;
        for (p; p > 1; p >>= 1) t[p>>1] = merge(t[p], t[p^1]);
    }
    
    F query(int l, int r) {  // sum on interval [l, r)
        F resl = 0, resr = 0;
        for (l += cnt, r += cnt; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = merge(resl, t[l++]);
            if (r&1) resr = merge(t[--r], resr);
        }
        return merge(resl, resr);
    }
};
