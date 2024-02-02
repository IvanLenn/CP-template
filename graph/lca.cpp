// dep 0-indexed;

int a[3000][15];
struct Lca{
    vi sz, dep;
    vector<vi> edge;
    const int L = 15;

    int root, n;
    Lca(vector<vi> &e, int r) {
        int N = (int)e.size();
        sz = vector<int>(N); dep = vector<int>(N);
        root = r;
        n = N;
        edge = e;
        for (int i = 0; i < n; i++) for (int j = 0; j < L; j++) a[i][j] = -1;
        dfs(r, -1);
        for (int i = 1; i < L; i++) {
            for (int v = 0; v < n; v++) {
                if (a[v][i - 1] != -1) a[v][i] = a[a[v][i - 1]][i - 1];
            }
        }
    }

    void dfs(int v, int pre) {
        if (pre != -1) dep[v] = dep[pre] + 1;
        sz[v] = 1;
        a[v][0] = pre;
        for (auto u : edge[v]) {
            if (u == pre) continue;
            dfs(u, v);
            sz[v] += sz[u];
        }
    }

    int lca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        int dif = dep[v] - dep[u];
        for (int i = 0; i < L; i++) if (dif & (1 << i)) v = a[v][i];
        if (u == v) return v;
        for (int i = L - 1; i >= 0; i--) {
            if (a[v][i] == a[u][i]) continue;
            v = a[v][i];
            u = a[u][i];
        }
        return a[v][0];
    }

    int dist(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        int Lca = lca(u, v);
        if (Lca == u) {
            return dep[v] - dep[u];
        }
        return dep[v] + dep[u] - 2 * dep[Lca];
    }

    int up(int v, int dis) {
        assert(dep[v] >= dis);
        for (int i = 0; i < L; i++) if (dis & (1 << i)) v = a[v][i];
        return v;
    }
};
