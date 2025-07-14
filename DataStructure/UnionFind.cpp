#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnionFind {
private:
    int n;
    vector<int> parent, siz;

    public:
    explicit UnionFind(int N) : n(N) {
        parent.resize(n);
        siz.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        assert(0 <= x && x < n);
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (siz[rootX] < siz[rootY]) swap(rootX, rootY);

        parent[rootY] = rootX;
        siz[rootX] += siz[rootY];
    }

    int size(int x) {
        assert(0 <= x && x < n);
        return siz[find(x)];
    }

    bool same(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        return (find(x) == find(y));
    }

    int count(void) {
        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (i == find(i)) ret++;
        }
        return ret;
    }

    void debug(void) {
        vector<vector<int>> group(n);
        for (int i = 0; i < n; i++) group[find(i)].emplace_back(i);
        for (int i = 0; i < n; i++) {
            if (!group[i].empty()) {
                cout << i << " : {";
                for (int j = 0; j < siz[i]; j++) {
                    if (j > 0) cout << ", ";
                    cout << group[i][j];
                }
                cout << "}" << endl;
            }
        }
    }
};