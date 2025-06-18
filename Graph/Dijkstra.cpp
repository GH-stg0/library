#include <bits/stdc++.h>
using namespace std;

/*
計算量 : O(|E|log|V|)
単一始点最短経路問題（負辺を含まない）を解くアルゴリズム

dist[i] = INF のとき，始点 から 頂点 i には到達不可能．
Dijkstra_Path(a, b, prev) で a ~ b の最短経路が求められる．
*/

template <typename T>
void Dijkstra(int start, vector<vector<pair<int, T>>> &graph, vector<T> &dist, vector<int> &prev) {
    using P = pair<T, int>;
    const auto INF = numeric_limits<T>::max();

    int N = graph.size();
    dist.resize(N, INF);
    prev.resize(N, -1);
    priority_queue<P, vector<P>, greater<P>> pq;
    
    dist[start] = T(0);
    pq.emplace(dist[start], start);

    while (!pq.empty()) {
        P p = pq.top();
        pq.pop();
        int pos = p.second;
        if (dist[pos] < p.first) continue;
        for (const auto &[nex, cost] : graph[pos]) {
            if (dist[nex] == INF || dist[pos] + cost < dist[nex]) {
                dist[nex] = dist[pos] + cost;
                prev[nex] = pos;
                pq.emplace(dist[nex], nex);
            }
        }
    }
}

vector<int> Dijkstra_Path(int start, int end, vector<int> &prev) {
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

    // ダイクストラ法
    vector<int> dist;
    vector<int> prev;
    Dijkstra<int>(0, g, dist, prev);

    // 始点 から 頂点 i までの最短距離を出力.
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) cout << "到達できません" << endl;
        else cout << dist[i] << endl;
    }

    // 始点 から 頂点 i までの最短経路を出力．
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) cout << "到達できません" << endl;
        else {
            auto path = Dijkstra_Path(0, i, prev);
            for (int j = 0; j < path.size(); j++) cout << path[j] << " ";
            cout << endl;
        }
    }

    return 0;
}
