#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    vector<int> change_count(N+2);
    for (int i = 0;  i < M; i++) {
        int left, right;
        cin >> left >> right;
        change_count[left]++;
        change_count[right+1]--;
    }
    for (int i = 1; i <= N; i++) {
        change_count[i] += change_count[i-1];
    }

    int min_remove_turret = INT_MAX;
    for (int i = 1; i <= N; i++) {
        min_remove_turret = min(min_remove_turret, change_count[i]);
    }
    cout << min_remove_turret << endl;
    return 0;
}
