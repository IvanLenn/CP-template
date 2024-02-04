struct Trie{
    vector<vi> tree;
    vi num;
    int ind;
    Trie() {
        num.clear(); tree.clear();
        ind = 1; num.resize(1); tree.resize(1, {-1, -1});
    }

    void insert(int x) { // insert x into trie
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (tree[cur][bit] == -1) {
                tree[cur][bit] = ind++;
                tree.push_back({-1, -1});
                num.eb(0);
                cur = ind - 1;
            }
            else cur = tree[cur][bit];
            if (i == 0) num[cur] = x;
        }
    }

    bool in(int x) { // check if x is in trie
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (tree[cur][bit] == -1) return false;
            cur = tree[cur][bit];
        }
        return true;
    }

    vi get_all() { // get all numbers in trie
        vi ans;
        if (ind == 1) return ans;
        function<void(int)> dfs = [&](int cur) {
            bool son = false;
            for (int i = 0; i < 2; i++) {
                if (tree[cur][i] != -1) {
                    son = true;
                    dfs(tree[cur][i]);
                }
            }
            if (!son) ans.eb(num[cur]);
        };
        dfs(0);
        return ans;
    }

    int max_xor(int x) { //find t in trie such that x xor t is maximum
        if (ind == 1) return 0;
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int need = bit ^ 1;
            if (tree[cur][need] != -1) cur = tree[cur][need];
            else cur = tree[cur][need ^ 1];
            if (i == 0) return num[cur];
        }
    }

    void all_xor(int x) {
        function<void(int, int)> dfs = [&](int cur, int pos) {
            if (pos == -1) {
                num[cur] ^= x;
                return;
            }
            int bit = (x >> pos) & 1;
            if (tree[cur][0] != -1) dfs(tree[cur][0], pos - 1);
            if (tree[cur][1] != -1) dfs(tree[cur][1], pos - 1);
            if (bit == 1) {
                swap(tree[cur][0], tree[cur][1]);
            }
        };
        dfs(0, 30);
    }
};

struct Trie{
    vector<vector<int>> tree;
    vector<int> num, cnt;
    int ind;
    Trie() {
        num.clear(); tree.clear(); cnt.clear();
        ind = 1; num.resize(1); tree.resize(1, {-1, -1});
        cnt.resize(1);
    }

    void insert(int x) { // insert x into trie
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (tree[cur][bit] == -1) {
                tree[cur][bit] = ind++;
                tree.push_back({-1, -1});
                num.push_back(0);
                cnt.push_back(0);
                cur = ind - 1;
            }
            else cur = tree[cur][bit];
            if (i == 0) {
                num[cur] = x;
                cnt[cur]++;
            }
        }
    }

    void del(int x) {
        int cur = 0;
        vector<int> pre(31), b(31);
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            pre[i] = cur;
            b[i] = bit;
            cur = tree[cur][bit];
            if (i == 0) {
                cnt[cur]--;
                if (cnt[cur] == 0) {
                    for (int j = 0; j <= 30; j++) {
                        tree[pre[j]][b[j]] = -1;
                        if (tree[pre[j]][b[j] ^ 1] != -1) break;
                    }
                }
            }
        }
    }

    bool in(int x) { // check if x is in trie
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (tree[cur][bit] == -1) return false;
            cur = tree[cur][bit];
        }
        return true;
    }


    int max_xor(int x) { //find t in trie such that x xor t is maximum
        if (ind == 1) return 0;
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int need = bit ^ 1;
            if (tree[cur][need] != -1) cur = tree[cur][need];
            else cur = tree[cur][need ^ 1];
            if (i == 0) {
                return num[cur];
            }
        }
        return 0;
    }
};
