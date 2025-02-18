#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<string> S(N);
    vector<string> T(M);

    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> T[i];
    }

    // 各開始位置(a,b)について探索
    for (int a = 0; a <= N - M; a++) {
        for (int b = 0; b <= N - M; b++) {
            bool match = true;
            // パターンTとの比較
            for (int j = 0; j < M && match; j++) {
                for (int k = 0; k < M && match; k++) {
                    if (T[j][k] != S[a + j][b + k]) {
                        match = false;
                    }
                }
            }
            // 完全一致した場合
            if (match) {
                cout << a + 1 << " " << b + 1 << endl;
                return 0;
            }
        }
    }

    return 0;
}