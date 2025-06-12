#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        vector<int> A(N * 2);
        vector<vector<int>> A_pos(N + 1);
        
        for (int j = 0; j < N * 2; j++) {
            cin >> A[j];
            A_pos[A[j]].push_back(j);
        }
        
        set<pair<int, int>> valid_pairs;
        
        for (int i = 0; i + 1 < N * 2; i++) {
            int a = A[i];
            int b = A[i + 1];
            
            // 同じ数字のペアは考慮しない
            if (a == b) continue;
            
            // a同士、b同士が隣接していない確認
            if (A_pos[a][0] + 1 == A_pos[a][1]) continue;
            if (A_pos[b][0] + 1 == A_pos[b][1]) continue;
            
            // 交換操作の効果を判定
            vector<int> v{A_pos[a][0], A_pos[a][1], A_pos[b][0], A_pos[b][1]};
            sort(v.begin(), v.end());
            
            if (v[0] + 1 == v[1] && v[2] + 1 == v[3]) {
                valid_pairs.emplace(minmax(a, b));  // 常にa<bの順で保存
            }
        }
        
        cout << valid_pairs.size() << endl;
    }
    return 0;
}
