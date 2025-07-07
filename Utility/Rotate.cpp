#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 右に 90 度回転
template<typename T>
vector<vector<T>> rotate_R(const vector<vector<T>> &vec) {
    const int H = vec.size();
    const int W = vec[0].size();
    vector<vector<T>> ret(W, vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[j][H-1-i] = vec[i][j]; 
    }
    return ret;
}

// 左に 90 度回転
template<typename T>
vector<vector<T>> rotate_L(const vector<vector<T>> &vec) {
    const int H = vec.size();
    const int W = vec[0].size();
    vector<vector<T>> ret(W, vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[W-1-j][i] = vec[i][j];
    }
    return ret;
}

// 180 度回転
template<typename T>
vector<vector<T>> rotate_U(const vector<vector<T>> &vec) {
    const int H = vec.size();
    const int W = vec[0].size();
    vector<vector<T>> ret(H, vector<T>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) ret[H-1-i][W-1-j] = vec[i][j];
    }
    return ret;
}
