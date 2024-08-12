#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define A first
#define B second
#define SZ(x) int(x.size())
#define FR(i, a, b) for (int i = (a); i < (b); i++)
#define FOR(i, b) FR(i, 0, b)
#define PB push_back
#define MP make_pair
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

double E = 0.0001;
bool get(const vector<double>& a, int target = 24, bool only_int = true, bool verbose = true) {
    if (only_int) {
        for (auto& i : a) {
            assert(abs(i - int(i)) <= E);
        }
    }
    int n = a.size();
    if (n == 1) {
        return abs(a[0] - target) <= E; // change target
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<double> b;
            for (int k = 0; k < n; k++) if (k != i && k != j) b.push_back(a[k]);
            b.push_back(a[i] + a[j]);
            if (get(b, target, only_int, verbose)) {
                if (verbose) cout << a[i] << " + " << a[j] << " = " << a[i] + a[j] << '\n';
                return true;
            }
            b.pop_back();
            b.push_back(a[i] - a[j]);
            if (get(b, target, only_int, verbose)) {
                if (verbose) cout << a[i] << " - " << a[j] << " = " << a[i] - a[j] << '\n';
                return true;
            }
            b.pop_back();
            b.push_back(a[j] - a[i]);
            if (get(b, target, only_int, verbose)) {
                if (verbose) cout << a[j] << " - " << a[i] << " = " << a[j] - a[i] << '\n';
                return true;
            }
            b.pop_back();
            b.push_back(a[i] / a[j]);
            if (a[j] && (!only_int || (int(a[i]) % int(a[j]) == 0)) && get(b, target, only_int, verbose)) {
                if (verbose) cout << a[i] << " / " << a[j] << " = " << a[i] / a[j] << '\n';
                return true;
            }
            b.pop_back();
            b.push_back(a[j] / a[i]);
            if (a[i] && (!only_int || (int(a[j]) % int(a[i]) == 0)) && get(b, target, only_int, verbose)) {
                if (verbose) cout << a[j] << " / " << a[i] << " = " << a[j] / a[i] << '\n';
                return true;
            }
            b.pop_back();
            b.push_back(a[j] * a[i]);
            if (get(b, target, only_int, verbose)) {
                if (verbose) cout << a[i] << " * " << a[j] << " = " << a[j] * a[i] << '\n';
                return true;
            }
        }
    }
    return false;
}

void solve_final() {
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve_final();
    }
}
