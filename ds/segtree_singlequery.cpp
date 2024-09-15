template<class F>
struct segtree{
    // modify: merge, modify, base case
    int cnt;  // array size
    F id;
    vector<F> t;

    segtree(int cnt, F& id) : cnt(cnt), id(id) {
        t.resize(2 * cnt, id);
    }
    
    inline F merge(F a, F b) {
        return a + b;
    }
    
    void modify(int l, int r, const F& value) {
        for (l += cnt, r += cnt; l < r; l >>= 1, r >>= 1) {
            if (l&1) {
                t[l] = merge(t[l], value);
                l++;
            }
            if (r&1) {
                r--;
                t[r] = merge(t[r], value);
            }
        }
    }
    
    F query(int p) {
        F res = id;
        for (p += cnt; p > 0; p >>= 1) res = merge(res, t[p]);
        return res;
    }
};
