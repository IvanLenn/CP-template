const int N = 4e5;  // limit for array size
int cnt;  // array size
int t[2 * N];
 
inline int merge(int a, int b) {
    return a + b;
}
 
void build() {  // build the tree
    for (int i = cnt - 1; i > 0; --i) {
        t[i] = merge(t[i<<1], t[i<<1|1]);
    }
}
 
void modify(int p, int value) {  // set value at position p
    p += cnt;
    t[p] += value;
 	for (p; p > 1; p >>= 1) t[p>>1] = merge(t[p], t[p^1]);
}
 
int query(int l, int r) {  // sum on interval [l, r)
    int resl = 0, resr = 0;
    for (l += cnt, r += cnt; l < r; l >>= 1, r >>= 1) {
        if (l&1) resl = merge(resl, t[l++]);
        if (r&1) resr = merge(t[--r], resr);
    }
    return merge(resl, resr);
}

