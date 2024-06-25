template<class F>
struct segtree{
    int cnt;
    vector<F> t;

    segtree(int cnt) : cnt(cnt) {
        t.resize(2 * cnt);
    }
    
    inline F merge(F a, F b) {
        return a + b;
    }
    
    void build() {
        for (int i = cnt - 1; i > 0; --i) {
            t[i] = merge(t[i<<1], t[i<<1|1]);
        }
    }
    
    void modify(int p, F value) {
        p += cnt;
        t[p] = value;
        for (p; p > 1; p >>= 1) t[p>>1] = (p&1?merge(t[p^1], t[p]):merge(t[p], t[p^1]));
    }
    
    F query(int l, int r) {
        F resl = 0, resr = 0;
        for (l += cnt, r += cnt; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = merge(resl, t[l++]);
            if (r&1) resr = merge(t[--r], resr);
        }
        return merge(resl, resr);
    }
};
