struct DSU {
    vector<int> p, sz;
    DSU(int n) {
        p.clear(); sz.clear();
        p.resize(n); sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int get(int x) {
        if (x == p[x]) return x;
        return p[x] = get(p[x]);
    }

    bool unite(int u, int v) {
        u = get(u); v = get(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        p[v] = u;
        sz[u] += sz[v];
        return true;
    }
}
