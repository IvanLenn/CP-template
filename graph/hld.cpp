// Tree rooted at r;
// sz: sizes of subtree;
// p: index of parent, p[root] = -1;
// son: index of heavest son, otherwise son[node] = -1;
// dep: depth of node, dep[root] = 0;
// top: original index of nodes at top of chain containing current node;
// to: relabeling of nodes, to[root] = 0;
// back: mapping from relabeling to original index;
// label of nodes in subtrees and chains consecutive

struct heavy_light_decomposition{
    vector<int> sz, p, son, dep, top, to, back;
    int root, cnt = -1;
    heavy_light_decomposition(vector<vi> &e, int r) {
        int N = (int)e.size();
        sz = vector<int>(N); p = vector<int>(N); son = vector<int>(N, -1); dep = vector<int>(N);
        top = vector<int>(N); to = vector<int>(N); back = vector<int>(N);
        root = r;
        dfs1(e, root, -1);
        dfs2(e, root, root);
    }

    void dfs1(vector<vi> &e, int u, int pre) {
        if (pre == -1) dep[u] = 0;
        else dep[u] = dep[pre] + 1;
        sz[u] = 1;
        p[u] = pre;
        int ma = -1;
        for (auto v : e[u]) {
            if (v == pre) continue;
            dfs1(e, v, u);
            sz[u] += sz[v];
            if (sz[v] > ma) {
                ma = sz[v];
                son[u] = v;
            }
        }
    }

    void dfs2(vector<vi> &e, int u, int st) {
        to[u] = ++cnt;
        back[cnt] = u;
        top[u] = st;
        if (son[u] == -1) return;
        dfs2(e, son[u], st);
        for (auto v : e[u]) {
            if (v == p[u] || v == son[u]) continue;
            dfs2(e, v, v);
        }
    }

    int lca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        if (top[u] == top[v]) return u;
        if (dep[top[u]] > dep[top[v]]) swap(u, v);
        return lca(u, p[top[v]]);
    }

    int dist(int u, int v) {
        int l = lca(u, v);
        return dep[u] + dep[v] - 2 * dep[l];
    }

};
