struct Kosaraju{
    vector<int> finish, start;
    vector<int> label;
    int n;
    int cnt;

    Kosaraju(int n, vector<vector<int>>& e) : n(n) {
        finish.resize(n);
        start.resize(n);
        label.resize(n, -1);
        vector<vector<int>> rev_e(n);
        for (int i = 0; i < n; i++) {
            for (auto v : e[i]) rev_e[v].push_back(i);
        }
        cnt = 1;
        for(int i = 0; i < n; i++) {
            if (start[i]) continue;
            auto dfs = [&](auto&& self, int u) -> void {
                start[u] = cnt++;
                for (auto v : e[u]) {
                    if (start[v]) continue;
                    self(self, v);
                }
                finish[u] = cnt++;
            };
            dfs(dfs, i);
        }
        vector<pair<int, int>> rev_finish(n);
        for (int i = 0; i < n; i++) rev_finish[i] = make_pair(finish[i], i);
        sort(rev_finish.rbegin(), rev_finish.rend());
        cnt = 0;
        for(int i = 0; i < n; i++) {
            if (label[rev_finish[i].second] >= 0) continue;
            auto dfs = [&](auto&& self, int u) -> void {
                label[u] = cnt;
                for (auto v : rev_e[u]) {
                    if (label[v] >= 0) continue;
                    self(self, v);
                }
            };
            dfs(dfs, rev_finish[i].second);
            cnt++;
        }
    }
};
