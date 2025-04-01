multiset<long long> lb, rb;
long long ls = 0, rs = 0;
auto rebalance = [&]() {
    while (lb.size() > x / 2) {
        auto iter = lb.begin();
        ls += *iter;
        rs -= *iter;
        rb.insert(-*iter);
        lb.erase(iter);
    }
    while (rb.size() > (x + 1) / 2) {
        auto iter = rb.begin();
        ls += *iter;
        rs -= *iter;
        lb.insert(-*iter);
        rb.erase(iter);
    }
};
auto add = [&](long long x) {
    if (rb.empty()) {
        lb.insert(-x);
        ls += x;
    }
    else {
        if (x >= *rb.begin()) {
            rb.insert(x);
            rs += x;
        }
        else {
            lb.insert(-x);
            ls += x;
        }
    }
};
auto erase = [&](long long x) {
    if (rb.count(x)) {
        auto iter = rb.find(x);
        rb.erase(iter);
        rs -= x;
    }
    else {
        assert(lb.count(-x));
        auto iter = lb.find(-x);
        lb.erase(iter);
        ls -= x;
    }
};