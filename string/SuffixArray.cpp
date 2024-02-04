//the function reads in a string s and string length n
//the function will return with p where p[i] means the ith smallest suffix starting point
//for "ababba", p = {6, 5, 0, 2, 4, 1, 3}
//omit the first element as it is '$'
//optimized with radix sort and all;

function<vi(string, int)> sufstr = [](string s, int n) -> vi {
        s += '$';
        n++;
        vi p(n), c(n);
        {
            vector<pair<char, int>> a(n);
            for (int i = 0 ; i < n ;i++) a[i] = make_pair(s[i], i);
            sort(a.begin(), a.end());
            for (int i = 0; i < n; i++) p[i] = a[i].second;
            c[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                if (a[i].first == a[i - 1].first) c[p[i]] = c[p[i - 1]];
                else c[p[i]] = c[p[i - 1]] + 1;
            }
        }
        int k = 0;
        while ((1 << k) < n) {
            for (auto& i : p) i = (i - (1 << k) + n) % n;
            function<void(vi&, vi&)> count_sort = [](vi &p, vi &c) -> void{
                int n = (int)p.size();
                vi cnt(n);
                for (auto i: c) cnt[i]++;
                vi p_new(n);
                vi pos(n);
                pos[0] = 0;
                for (int i = 1; i < n; i++) {
                    pos[i] = pos[i - 1] + cnt[i - 1];
                }
                for (auto x : p) {
                    int i = c[x];
                    p_new[pos[i]] = x;
                    pos[i]++;
                }
                p = p_new;
            };
            count_sort(p, c);
            vi c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pi cur = make_pair(c[p[i]], c[(p[i] + (1 << k)) % n]);
                pi pre = make_pair(c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]);
                if (pre == cur) c_new[p[i]] = c_new[p[i - 1]];
                else c_new[p[i]] = c_new[p[i - 1]] + 1;
            }
            c = c_new;
            k++;
        }
        return p;
    };
