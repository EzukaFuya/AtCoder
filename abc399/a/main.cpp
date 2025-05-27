#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S,T;
    cin >> N >> S >> T;

    int counter = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] != T[i]) {
            counter++;
        }
    }

    cout << counter << endl;
    
    return 0;
}