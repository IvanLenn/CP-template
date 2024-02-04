class MillerRabin{
    const vector<int> plist = {2, 7, 61};

    int QuickPow(int base, int p, const int m) {
        if (p == 0) return 1;
        if (p == 1) return base % m;
        int tmp = QuickPow(base, p / 2, m);
        tmp = (ll)tmp * tmp % m;
        if (p & 1) return (ll)tmp * base % m;
        return tmp;
    }
public:
    bool PrimeTest(int n) {
        if (n < 3 || n % 2 == 0) return n == 2;
        int u = n - 1, t = 0;
        while (u % 2 == 0) {
            u /= 2;
            t++;
        }

        for (int i = 0; i < plist.size(); i++) {
            int a = plist[i], v = QuickPow(a, u, n);
            if (v == 1) continue;
            int s = 0;
            while (s < t) {
                if (v == n - 1) break;
                v = (ll)v * v % n;
                s++;
            }
            if (s == t) return false;
        }
        return true;
    }

    bool BruteTest(ll n) {
        if (n <= 10) {
            for (ll i = 2; i < n; i++) if (n % i == 0) return false;
            return true;
        }
        for (ll i = 2; i <= (ll)sqrt(n) + 1; i++) if (n % i == 0) return false;
        return true;
    }

    // generates a prime in range [l, r)
    int Generate(int l, int r) {
        while (true) {
            int t = ((ll)rnd() % (r - l)) + l;
            if (PrimeTest(t)) return t;
        }
    }
};
