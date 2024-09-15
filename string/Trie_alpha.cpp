// char size
const int K = 26;
struct Vertex{
    int next[K];
    bool output = false;
    Vertex() {
        for (int i = 0; i < K; i++) next[i] = -1;
    }
};

struct Trie{
    vector<Vertex> trie;
    Trie() {
        trie.resize(1);
    }

    void add(const string& s) {
        int n = s.size();
        int idx = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (trie[idx].next[c] != -1) {
                idx = trie[idx].next[c];
                continue;
            }
            trie[idx].next[c] = (int)(trie.size());
            idx = int(trie.size());
            trie.PB(Vertex());
        }
        trie[idx].output = true;
    }
};
