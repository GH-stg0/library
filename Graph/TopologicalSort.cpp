#include <bits/stdc++.h>
using namespace std;

/* 
計算量 : O(|V|+|E|)
有向非巡回グラフ (DAG) の頂点を一列に並べたとき，すべての辺が左から右に向かうような順序（トポロジカル順序）を求めるアルゴリズム

ret が 空配列 = 閉路が存在する． (DAG でない)
ret には，全頂点がトポロジカル順序に並べられている．
*/

vector<int> TopologicalSort(vector<vector<int>> &graph) {
    int N = graph.size();

    vector<int> indegree(N, 0);
    for (int pos = 0; pos < N; pos++) {
        for (const int nex : graph[pos]) indegree[nex]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; i++) {
      if (indegree[i] == 0) pq.push(i);
    }

    vector<int> ret;
    while (!pq.empty()) {
        int pos = pq.top();
        pq.pop();
        ret.emplace_back(pos);
        for (const int &nex : graph[pos]) {
            indegree[nex]--;
            if (indegree[nex] == 0) pq.push(nex);
        }
    }

    if (ret.size() < N) return {};
    else return ret;
}

int main() {
    // グラフを構築
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
    }
    
    // トポロジカルソート
    vector<int> ts = TopologicalSort(g);
    
    // DAG の判定
    if (ts.empty()) cout << "閉路が存在します" << endl;
    else {
        cout << "有向非巡回グラフ (DAG) です" << endl;
        for (int i = 0; i < ts.size(); i++) cout << ts[i] << endl;
    }

    return 0;
}