#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    if (N % 2 == 0) {
        for (int i = 0; i < N; i++) {
            if (i == N/2 || i == N/2-1) {
                cout << "=";
            }
            else {
                cout << "-";
            }
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            if (i == N/2) {
                cout << "=";
            }
            else {
                cout << "-";
            }
        }
    }
    cout << endl;
    return 0;
}