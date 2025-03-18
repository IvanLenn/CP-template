// addition op and max query
struct S {LL mx;};
struct F {LL add;};
S op(S l, S r) { return S{max(l.mx, r.mx)}; }
S e() { return S{0LL}; }
S mapping(F f, S x) { return S{x.mx + f.add}; }
F composition(F f, F g) { return F{f.add + g.add}; }
F id() { return F{0}; }

template <
        class S,S(*op)(S, S),S(*e)(),
        class F,S(*mapping)(F, S),F(*composition)(F, F),F(*id)()>
class Segtree {
public:
    vector<S>node;
    vector<S>d;
    vector<F>lz;
    int _n;

    void build(int x, int lx, int rx) {
        if (lx == rx - 1) {
            node[x] = d[lx];
            return;
        }
        int mid = (lx + rx) / 2;
        build(2 * x + 1, lx, mid);
        build(2 * x + 2, mid, rx);
        node[x] = op(node[2 * x + 1], node[2 * x + 2]);
    }

    Segtree(int n) {
        _n = n;
        d = vector<S>(n, e());
        node = vector<S>(4 * n, e());
        lz = vector<F>(4 * n, id());
        build(0, 0, n);
    }

    Segtree(vector<S> &a, int n) {
        _n = n;
        d = a;
        node = vector<S>(4 * n, e());
        lz = vector<F>(4 * n, id());
        build(0, 0, n);
    }

    void push(int rt, F x) {
        node[rt] = mapping(x, node[rt]);
        lz[rt] = composition(x, lz[rt]);
    }

    void push_down(int x) {
        push(2 * x + 1, lz[x]);
        push(2 * x + 2, lz[x]);
        lz[x] = id();
    }

    S get(int x, int lx, int rx, int que_L, int que_R) {
        if (lx >= que_R || rx <= que_L)return e();
        if (que_L <= lx && rx <= que_R)return node[x];
        int mid = (lx + rx) / 2;
        push_down(x);
        return op(
                get(2 * x + 1, lx, mid, que_L, que_R),
                get(2 * x + 2, mid, rx, que_L, que_R)
        );
    }
    S get(int l, int r) {
        return get(0, 0, _n, l, r);
    }

    void modify(int x, int lx, int rx, int que_L, int que_R, F elem) {
        if (lx >= que_R || rx <= que_L) return;
        if (que_L <= lx && rx <= que_R) {
            push(x, elem);
            return;
        }
        int mid = (lx + rx) / 2;
        push_down(x);
        modify(2 * x + 1, lx, mid, que_L, que_R, elem);
        modify(2 * x + 2, mid, rx, que_L, que_R, elem);
        node[x] = op(node[2 * x + 1], node[2 * x + 2]);
    }
    void modify(int l, int r, F x) {
        cout << l << ' ' << r << ' ' << x.add << '\n';
        modify(0, 0, _n, l, r, x);
    }

};

Segtree<S, op, e, F, mapping, composition, id> T(n);
