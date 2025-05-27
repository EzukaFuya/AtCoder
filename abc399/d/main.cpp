#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        vector<int> A(N * 2);
        vector<vector<int>> A_pos(N + 1);

        for (int j = 0; j < N * 2; j++) {
            cin >> A[j];
            A_pos[A[j]].push_back(j);
        }
        
        int counter = 0;
        vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));

        for (int i = 0; i + 1 < N * 2; i++) {
            int a = A[i];
            int b = A[i + 1];

            if (A_pos[a][0] + 1 == A_pos[a][1]) continue;
            if (A_pos[b][0] + 1 == A_pos[b][1]) continue;

            vector<int> v{A_pos[a][0], A_pos[a][1], A_pos[b][0], A_pos[b][1]};
            sort(v.begin(), v.end());
            if (v[0] + 1 == v[1] && v[2] + 1 == v[3]) {
                if (!visited[a][b]) {
                    counter++;
                    visited[a][b] = true;
                }
            }
        }

        cout << counter << endl;

    }
    return 0;
}
