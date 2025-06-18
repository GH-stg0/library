#include <bits/stdc++.h>
using namespace std;

/*
計算量 : O(|V|^3)
全点対最短経路問題（負辺を含んでよい）を解くアルゴリズム

dist[i][i] < 0 となる i が存在する場合，負閉路が存在する．
dist[i][j] = INF のとき，頂点 i から 頂点 j には到達不可能． 
*/

template <typename T>
void FloydWarshall(vector<vector<pair<int, T>>> &graph, vector<vector<T>> &dist, vector<vector<int>> &prev) {
    const auto INF = numeric_limits<T>::max();

    int N = (int)graph.size();
    dist.resize(N, vector<int>(N, INF));
    prev.resize(N, vector<int>(N, -1));

    for (int pos = 0; pos < N; pos++) {
        dist[pos][pos] = 0;
        prev[pos][pos] = pos;
        for (auto &[nex, cost] : graph[pos]) {
            dist[pos][nex] = cost;
            prev[pos][nex] = pos;
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                else if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prev[i][j] = prev[k][j];
                }
            }
        }
    }
}

vector<int> FloydWarshall_Path(int start, int end, vector<vector<int>> &prev) {
    vector<int> ret;
    for (int cur = end; cur != start; cur = prev[start][cur]) ret.emplace_back(cur);
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

    // ワーシャル・フロイド法
    vector<vector<int>> dist;
    vector<vector<int>> prev;
    FloydWarshall<int>(g, dist, prev);

    // 負閉路の検出
    bool check = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) check = true;
    }
    if (check) cout << "グラフに負閉路が存在します" << endl;

    // 頂点 i から 頂点 j までの最短距離を出力(負閉路が存在しない場合)
    if (!check) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][i] == INT_MAX) cout << "到達できません" << endl;
                else cout << dist[i][j] << endl;
            }
            cout << endl;
        }
    }

    // 頂点 i から 頂点 j までの最短経路を出力(負閉路が存在しない場合)
    if (!check) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INT_MAX) cout << "到達できません " << endl;
                else {
                    auto path = FloydWarshall_Path(i, j, prev);
                    for (int k = 0; k < path.size(); k++) cout << path[k] << " ";
                    cout << endl;
                }
            }
            cout << endl;
        }
    }
}
