#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // vector<int> u(M);
    // vector<int> v(M);

    int counter = 0;
    set<pair<int, int>> hen;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        if (hen.count({u, v}) == 0 && hen.count({v, u}) == 0
            && u != v) {
            hen.insert({u, v});
        }
        else {
            counter++;
        }
    }

    cout << counter << endl;

    return 0;
}