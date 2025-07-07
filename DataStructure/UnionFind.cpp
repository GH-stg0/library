#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class UnionFind {
public:
    vector<int> parent, siz;
    UnionFind(size_t n) {
        parent.resize(n);
        siz.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (siz[rootX] < siz[rootY]) swap(rootX, rootY);

        parent[rootY] = rootX;
        siz[rootX] += siz[rootY];
    }

    int size(int x) {
        return siz[find(x)];
    }

    bool same(int x, int y) {
        return (find(x) == find(y));
    }
};