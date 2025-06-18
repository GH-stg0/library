#include <bits/stdc++.h>
using namespace std;

/*
計算量 : O(|N|loglog|N|)
与えられた数以下の素数を全て見つけるアルゴリズム

ret[i] = true  のとき，i は素数
*/

vector<bool> Eratosthenes(int N) {
    vector<bool> ret(N+1, true);
    ret[0] = false;
    ret[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (ret[i] == false) continue;
        for (int j = i * 2; j <= N; j += i) ret[j] = false;
    }
    return ret;
}

int main() {
    int n;
    cin >> n;

    // エラトステネスの篩
    auto isp = Eratosthenes(n);

    for (int i = 0; i <= n; i++) {
        if (isp[i] == true) cout << i << " は素数です" << endl;
        else cout << i << " は合成数です" << endl; 
    }

    return 0;
}
