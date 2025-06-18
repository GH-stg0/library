#include <bits/stdc++.h>
using namespace std;

/*
計算量 : O(|V||E|)
単一始点最短経路問題（負辺を含んでよい）を解くアルゴリズム

dist[i] = -INF となる i が存在するとき，負閉路が存在する．
dist[i] =  INF のとき，始点 から 頂点 i には到達不可能．
dist[i] = -INF のとき，頂点 i は負閉路を用いてコストを無限に減少させられる．
BellmanFord_Path(a, b, prev) で a ~ b の最短経路が求められる．
*/

template <typename T>
void BellmanFord(int start, vector<vector<pair<int, T>>> &graph, vector<T> &dist, vector<int> &prev) {
    const auto INF = numeric_limits<T>::max();

    int N = graph.size();
    dist.resize(N, INF);
    prev.resize(N, -1);

    dist[start] = T(0);

    for (int cnt = 1; cnt <= N - 1; cnt++) {
        bool changed = false;
        for (int pos = 0; pos < N; pos++) {
            for (const auto &[nex, cost] : graph[pos]) {
                if (dist[pos] == INF) continue;
                else if (dist[pos] + cost < dist[nex]) {
                    dist[nex] = dist[pos] + cost;
                    prev[nex] = pos;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    vector<bool> seen(N, false);
    auto dfs = [&](auto self, int pos) -> void {
        seen[pos] = true;
        dist[pos] = -INF;
        for (const auto &[nex, cost] : graph[pos]) {
            if (!seen[nex]) self(self, nex);
        }
    };

    for (int pos = 0; pos < N; pos++) {
        if (dist[pos] == INF) continue;
        for (const auto &[nex, cost] : graph[pos]) {
            if (dist[pos] + cost < dist[nex] && !seen[nex]) dfs(dfs, nex);
        }
    }
}

vector<int> BellmanFord_Path(int start, int end, vector<int> &prev) {
    vector<int> ret;
    for (int pos = end; pos != start; pos = prev[pos]) ret.push_back(pos);
    ret.emplace_back(start);
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    // グラフを構築
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
    } 

    // ベルマンフォード法
    vector<int> dist;
    vector<int> prev;
    BellmanFord<int>(0, g, dist, prev);

    // 負閉路の検出
    bool check = false;
    for (int i = 0; i < n; i++) {
        if (dist[i] == -INT_MAX) check = true;
    }
    if (check) cout << "グラフに負閉路が存在します" << endl;

    // 始点 から 頂点 i までの最短距離を出力
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) cout << "到達できません" << endl;
        else if (dist[i] == -INT_MAX) cout << "最小値が存在しません" << endl;
        else cout << dist[i] << endl;
    }

    // 始点 から 頂点 i までの最短経路を出力
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) cout << "到達できません" << endl;
        else if (dist[i] == -INT_MAX) cout << "最短経路が存在しません" << endl;
        else {
            auto path = BellmanFord_Path(0, i, prev);
            for (int j = 0; j < path.size(); j++) cout << path[j] << " ";
            cout << endl;
        }
    }

    return 0;
}
