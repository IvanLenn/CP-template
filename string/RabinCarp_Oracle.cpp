class RabinKarp{
    // Need M ~ 2kN^2/4 * log(kN^2/4) for error < 1/k worst case
    // int p;
    const int p = 1e9 + 7;
    int n, b;
    vector<int> exp, a, reva;

public:
    RabinKarp(string& s) {
        b = 256;
        vector<int> S;
        for (auto c : s) S.push_back((int)c);
        init(S);
    }

    RabinKarp(vector<int>& S, int base) {
        b = base;
        init(S);
    }

    void init(vector<int>& s) {
        // MillerRabin T;
        // p = T.Generate(1 << 28, 1 << 29);
        n = s.size();
        a.resize(n + 1);
        exp.resize(n + 1);
        reva.resize(n + 1);
        exp[0] = 1;
        for (int i = 1; i <= n; i++) exp[i] = ((long long)exp[i - 1] * b) % p;
        for (int i = 1; i <= n; i++) a[i] = ((long long)a[i - 1] * b + s[i - 1]) % p;
        for (int i = n - 1; i >= 0; i--) reva[i] = ((long long)reva[i + 1] * b + s[i]) % p;
    }

    // 0-indexed, exclusive right endpoint
    int hash(int l, int r) {
        int ret = (-1ll * a[l] * exp[r - l]) % p;
        return (ret + p + a[r]) % p;
    }

    // 0-indexed, exclusive right endpoint
    int revhash(int l, int r) {
        int ret = (-1ll * reva[r] * exp[r - l]) % p;
        return (ret + p + reva[l]) % p;
    }
};
