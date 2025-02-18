#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 1. 入力
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int n;
    ll s;
    cin >> n >> s;
    
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 2. 全体の和を求める
    ll total = 0;
    for(int i = 0; i < n; i++) {
        total += a[i];
    }
    
    // 3. 目標値を計算（全体の和で割った余り）
    ll target = s % total;
    
    // 4. しゃくとり法で解く
    int left = 0;    // 左端
    int right = 0;   // 右端
    ll sum = 0;      // 現在の区間の和
    
    // 5. 区間を伸縮させながら探索
    while(right < 2*n && left < n) {
        // 和が目標より小さい場合は右を伸ばす
        if(sum < target) {
            sum += a[right % n];
            right++;
        }
        // 和が目標より大きい場合は左を縮める
        else if(sum > target) {
            sum -= a[left];
            left++;
        }
        // 和が目標と等しい場合は終了
        else {
            cout << "Yes" << endl;
            return 0;
        }
    }
    
    // 6. 見つからなかった場合
    cout << "No" << endl;
    return 0;
}