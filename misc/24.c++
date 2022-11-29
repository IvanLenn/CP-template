#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const ll LNF = 1e18;
#define F first
#define S second
#define eb emplace_back
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vll;
typedef vector<vector<int>> vii;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
const int M = (1e9) + 7;

int sum() { return 0; }

template<typename T, typename... Args>
T sum(T a, Args... args) { return a + sum(args...); }

template<typename... T>
void read(T &...args) { ((cin >> args), ...); }

template<typename... T>
void write(string delimiter, T &&...args) { ((cout << args << delimiter), ...); }

template<typename T>
void readc(T &t) { for (auto &e: t) { read(e); }}

template<typename T>
void writec(string delimiter, T &t) {
    for (const auto &e: t) { write(delimiter, e); }
    write("\n");
}

template<typename ...T>
void printer(T &&... args) { ((cout << args << " "), ...); }

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}

template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}

double E = 0.0001;
bool get(vector<double> a) {
    int n = a.size();
    if (n == 1) {
        return abs(a[0] - 24) <= E; // change target
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<double> b;
            for (int k = 0; k < n; k++) if (k != i && k != j) b.eb(a[k]);
            b.eb(a[i] + a[j]);
            if (get(b)) {
                cout << a[i] << " + " << a[j] << " = " << a[i] + a[j] << '\n';
                return true;
            }
            b.pop_back();
            b.eb(a[i] - a[j]);
            if (get(b)) {
                cout << a[i] << " - " << a[j] << " = " << a[i] - a[j] << '\n';
                return true;
            }
            b.pop_back();
            b.eb(a[j] - a[i]);
            if (get(b)) {
                cout << a[j] << " - " << a[i] << " = " << a[j] - a[i] << '\n';
                return true;
            }
            b.pop_back();
            b.eb(a[i] / a[j]);
            if (get(b)) {
                cout << a[i] << " / " << a[j] << " = " << a[i] / a[j] << '\n';
                return true;
            }
            b.pop_back();
            b.eb(a[j] / a[i]);
            if (get(b)) {
                cout << a[j] << " / " << a[i] << " = " << a[j] / a[i] << '\n';
                return true;
            }
            b.pop_back();
            b.eb(a[j] * a[i]);
            if (get(b)) {
                cout << a[i] << " * " << a[j] << " = " << a[j] * a[i] << '\n';
                return true;
            }
        }
    }
    return false;
}

void solve_final() {
    vector<double> a(4); //can change number of inputs
    readc(a);
    if (!get(a)) cout << "NO\n";
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
