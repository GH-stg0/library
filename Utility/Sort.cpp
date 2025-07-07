#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 絶対値順
template<typename T>
bool abs_order(T &left, T &right) {
    return abs(left) < abs(right);   
}

// first昇順 firstが同値の場合second降順
template <typename T1, typename T2>
bool asc_desc(pair<T1, T2> &left, pair<T1, T2> &right) {
    if (left.first == right.first) return right.second < left.second;
    else return left.first  < right.first;
}

// first降順 firstが同値の場合second昇順
template <typename T1, typename T2>
bool desc_asc(pair<T1, T2> &left, pair<T1, T2> &right) {
    if (left.first == right.first) return left.second < right.second;
    else return right.first < left.first;
}
