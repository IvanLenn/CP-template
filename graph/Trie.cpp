// char size
const int K = 26;
struct Vertex{
    int next[K];
    bool output = false;
    Vertex() {
        FOR(i, K) next[i] = -1;
    }
};

struct Trie{
    vector<Vertex> trie;
    Trie() {
        trie.resize(1);
    }

    void add(const string& s) {
        int n = SZ(s);
        int idx = 0;
        FOR(i, n) {
            int c = s[i] - 'a';
            if (trie[idx].next[c] != -1) {
                idx = trie[idx].next[c];
                continue;
            }
            trie[idx].next[c] = SZ(trie);
            idx = SZ(trie);
            trie.PB(Vertex());
        }
        trie[idx].output = true;
    }
};
