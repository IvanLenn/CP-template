struct hld{
    vector<int> p, son, sz, dep, top, label, inv_label;
    int cnt = 0, root = 0, n;
    hld(vector<vector<int>>& e, int root) : root(root) {
        n = SZ(e);
        sz.resize(n); son.resize(n, -1); p.resize(n); dep.resize(n); top.resize(n);
        label.resize(n); inv_label.resize(n);
        auto dfs1 = [&](auto&& self, vector<vector<int>>& e, int u, int pre) -> void {
            if (pre >= 0) dep[u] = dep[pre] + 1;
            sz[u] = 1;
            p[u] = pre;
            int mx = -1;
            for (auto v : e[u]) {
                if (v == pre) continue;
                self(self, e, v, u);
                sz[u] += sz[v];
                if (sz[v] > mx) {
                    mx = sz[v];
                    son[u] = v;
                }
            }
        };
        auto dfs2 = [&](auto&& self, vector<vector<int>> &e, int u, int up) -> void {
            inv_label[cnt] = u;
            label[u] = cnt++;
            top[u] = up;
            if (son[u] == -1) return;
            self(self, e, son[u], up);
            for (auto v : e[u]) {
                if (v == p[u] || v == son[u]) continue;
                self(self, e, v, v);
            }
        };
        dfs1(dfs1, e, root, -1);
        dfs2(dfs2, e, root, root);
    }
 
    int lca(int u, int v) {
        if (top[u] == top[v]) return abs(dep[u] - dep[v]);
        if (dep[top[u]] > dep[top[v]]) swap(u, v);
        return lca(u, p[top[v]]);
    }
};
