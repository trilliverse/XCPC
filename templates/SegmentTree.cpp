template <class Info>
struct SegmentTree {
    int n;
    vector<Info> info;
    SegmentTree() {}
    SegmentTree(int _n, Info _v = Info()) {
        init(_n, _v);
    }
    template <class T>
    SegmentTree(vector<T> _init) {
        init(_init);
    }
    void init(int _n, Info _v = Info()) {
        init(vector(_n, _v));
    }

    template <class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int mid = l + r >> 1;
            build(p<<1, l, mid);
            build(p<<1|1, mid, r);
            pushup(p);
        };
        build(1, 0, n);
    }
    void pushup(int pos) {
        info[pos] = info[pos << 1] + info[pos << 1 | 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int mid = l + r >> 1;
        if (x < mid)
            modify(p << 1, l, mid, x, v);
        else
            modify(p << 1 | 1, mid, r, x, v);
        pushup(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info query(int p, int l, int r, int x, int y) {  // [x, y)
        if (r <= x || l >= y)
            return Info();
        if (x <= l && r <= y)
            return info[p];
        int mid = l + r >> 1;
        return query(p << 1, l, mid, x, y) + query(p << 1 | 1, mid, r, x, y);
    }
    Info query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};

struct Info {
    // ll sum;
    // ll ls;
    // ll rs;
    // ll mx;
    // Info(ll s = 0) : sum(s), ls(s), rs(s), mx(s) {}
};

Info operator+(const Info &a, const Info &b) {
    Info res;
    // res.sum = a.sum + b.sum;
    // 
    return res;
}