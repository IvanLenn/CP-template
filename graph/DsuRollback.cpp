// No path compression and Yes small-to-large
// p: precurssor of current node, p[head of CC] = itself;
// sz: size of CC, only maintained for head;
// ops: stack of operations, store for roll_back;

struct DSU {
    vector<int> p, sz; //parent array and size array sz are strictly positive
    vector<pair<int, int>> ops;
    void init(int n) {
        p.clear(); sz.clear();
        p.resize(n);
        sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int get(int x) {
        while (x != p[x]) x = p[x];
        return x;
    }

    bool unite(int u, int v) {
        u = get(u); v = get(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        ops.emplace_back(v, p[v]);
        p[v] = u;
        ops.emplace_back(~u, sz[u]);
        sz[u] += sz[v];
        return true;
    }

    //roll_back will roll back till the size of ops is t
    void roll_back(int t) {
        while (ops.size() > t) {
            int i = ops.back().first;
            int j = ops.back().second;
            ops.pop_back();
            if (i >= 0) p[i] = j;
            else sz[~i] = j;
        }
    }
};
