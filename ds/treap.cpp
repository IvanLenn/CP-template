struct item {
    int key, prior, cnt, subtree_cnt;
    item *l, *r;
    item () { }
    item (int key, int cnt) : key(key), prior(rand()), cnt(cnt), subtree_cnt(cnt), l(NULL), r(NULL) { }
    item (int key, int prior, int cnt) : key(key), prior(prior), cnt(cnt), subtree_cnt(cnt), l(NULL), r(NULL) { }
};
typedef item* pitem;

int get(pitem t) {
    return t?t->subtree_cnt:0;
}

void update(pitem t) {
    if (t) {
        t->subtree_cnt = t->cnt + get(t->l) + get(t->r);
    }
}

void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = NULL;
    else if (t->key <= key)
        split (t->r, key, t->r, r),  l = t;
    else
        split (t->l, key, l, t->l),  r = t;
    update(t);
}

void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior) {
        split (t, it->key, it->l, it->r),  t = it;
    }
    else
        insert (t->key <= it->key ? t->r : t->l, it);
    update(t);
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior) {
        merge (l->r, l->r, r),  t = l;
    }
    else {
        merge (r->l, l, r->l),  t = r;
    }
    update(t);
}

void erase (pitem & t, int key) {
    if (t->key == key) {
        pitem th = t;
        merge (t, t->l, t->r);
        delete th;
    }
    else
        erase (key < t->key ? t->l : t->r, key);
    update(t);
}

pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    update(l);
    return l;
}
