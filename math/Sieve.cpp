// Linear sieve

vector<int> fac;
vi prime;
void init(int n) {
    fac.resize(n + 1);
    iota(fac.begin(), fac.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (fac[i] == i) prime.push_back(i);
        for (auto j : prime) {
            if (i * j > n) break;
            fac[i * j] = j;
            if (i % j == 0) break;
        }
    }
}

// Sieve of Eratosthenes;
vector<int> fact;
void init(int n) {
    fact.resize(n + 1);
    iota(fact.begin(), fact.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (fact[i] != i) continue;
        for (int j = i; j <= n; j+=i) {
            fact[j] = i;
        }
    }
}
