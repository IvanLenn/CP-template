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
    
    void modify(int l, int r, const F& value) {
        for (l += cnt, r += cnt; l < r; l >>= 1, r >>= 1) {
            if (l&1) t[l++] += value;
            if (r&1) t[--r] += value;
        }
    }
    
    F query(int p) {
        F res = 0;
        for (p += cnt; p > 0; p >>= 1) res = merge(res, t[p]);
        return res;
    }
};
