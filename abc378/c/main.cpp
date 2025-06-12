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
    
    map<int, int> map_num;
    
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;

        if (map_num.find(num) == map_num.end()) {
            map_num[num] = i;
            cout << -1;
        }
        else {
            int last_num_idx;
            last_num_idx = map_num[num] + 1;
            cout << last_num_idx;
            map_num[num] = i;
        }
        
        if (i != N - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
