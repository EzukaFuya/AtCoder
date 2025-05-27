#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    int max_length = 0;
    
    // 偶数インデックスから開始
    vector<int> last(N + 1, -2);  // 各値の最後の出現位置
    int left = 0;  // 現在の有効範囲の左端
    
    for (int i = 0; i + 1 < N; i += 2) {
        if (A[i] != A[i + 1]) {
            // ペアが等しくない → 次から新しく開始
            left = i + 2;
        } else {
            // ペアが等しい → この値の前回位置を考慮
            left = max(left, last[A[i]] + 2);
            
            // 長さを計算して更新
            int length = i + 2 - left;
            max_length = max(max_length, length);
            
            // この値の位置を記録
            last[A[i]] = i;
        }
    }
    
    // 奇数インデックスから開始
    fill(last.begin(), last.end(), -2);
    left = 1;
    
    for (int i = 1; i + 1 < N; i += 2) {
        if (A[i] != A[i + 1]) {
            left = i + 2;
        } else {
            left = max(left, last[A[i]] + 2);
            
            int length = i + 2 - left;
            max_length = max(max_length, length);
            
            last[A[i]] = i;
        }
    }
    
    cout << max_length << endl;
    return 0;
}