#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T>
struct SegmentTree {
private:
    int n;
    vector<T> data;
    function<T(T, T)> op;
    T e;

public:
    explicit SegmentTree(int N, function<T(T, T)> op, T e) : op(op), e(e) {
        n = 1;
        while (n < N) n *= 2;
        data.resize(2 * n, e);
    }

    void set(int p, T x) {
        assert(0 <= p && p < n);
        data[n + p] = x;
    }

    void build(void) {
        for (int i = n - 1; i >= 0; i--) {
            data[i] = op(data[2 * i], data[2 * i + 1]);
        }
    }

    void update(int p, T x) {
        assert(0 <= p && p < n);
        int pos = n + p;
        data[pos] = x;
        while (pos > 1) {
            pos /= 2;
            data[pos] = op(data[pos * 2], data[pos * 2 + 1]);
        }
    }

    T get(int p) {
        assert(0 <= p && p < n);
        return data[n + p];
    }

    T query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        T res_l = e, res_r = e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_l = op(res_l, data[l++]);
            if (r & 1) res_r = op(data[--r], res_r);
        }
        return op(res_l, res_r);
    }

    void debug(void) {
        cout << "data = {";
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ", ";
            cout << data[n + i];
        }
        cout << "}" << endl;
    }
};