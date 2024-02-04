// O(N) interpolation for n-degree polynomial;
// Need x values to form arithemetic sequence;


struct Interpolation{
    vector<vector<Mint>> point;
    Interpolation(vector<vector<Mint>>& point) : point(point) {}
    Mint get(Mint x) { // need point to be sorted and form arithmetic sequence
        int n = point.size();
        C(n, n / 2);
        Mint d = point[1][0] - point[0][0];
        vector<Mint> pref(n + 1, 1), surf(n + 1, 1);
        Mint acc = 1;
        for (int i = 1; i < n; i++) acc /= d;
        for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] * (x - point[i - 1][0]);
        for (int i = n - 1; i >= 0; i--) surf[i] = surf[i + 1] * (x - point[i][0]);
        Mint ans = 0;
        for (int i = 0; i < n; i++) {
            Mint tmp = point[i][1];
            tmp *= pref[i] * surf[i + 1];
            tmp *= inv_fact[i];
            tmp *= inv_fact[n - i - 1];
            tmp *= acc;
            if ((n - i - 1) & 1) ans -= tmp;
            else ans += tmp;
        }
        return ans;
    }
};
