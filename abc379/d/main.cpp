#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Q;
    cin >> Q;
    
    ll total_growth = 0;  // これまでの総成長量
    vector<ll> plants;    // 各植物が植えられた時点での total_growth
    
    for (int i = 0; i < Q; i++) {
        int que;
        cin >> que;
        
        switch(que) {
            case 1: {
                // 植物を植える（現在のtotal_growthを記録）
                plants.push_back(total_growth);
                break;
            }
            case 2: {
                int T;
                cin >> T;
                // 全植物がT成長 = total_growthをT増加
                total_growth += T;
                break;
            }
            case 3: {
                int H;
                cin >> H;
                
                // 植物の現在の高さ = total_growth - 植えた時のtotal_growth
                // 高さ >= H の条件: total_growth - plant_growth >= H
                // つまり plant_growth <= total_growth - H
                ll threshold = total_growth - H;
                
                // ソートして条件を満たす植物を数える
                sort(plants.begin(), plants.end());
                auto upper_itr = upper_bound(plants.begin(), plants.end(), threshold);
                
                ll counter = distance(plants.begin(), upper_itr);
                
                // 収穫した植物を削除
                plants.erase(plants.begin(), upper_itr);
                
                cout << counter << endl;
                break;
            }
        }
    }
    return 0;
}

/*
動作例（Sample Input 1）:
1. 植物植える: plants=[0], total_growth=0
2. 15日経過: plants=[0], total_growth=15
   → 植物の高さ = 15-0 = 15
3. 植物植える: plants=[0,15], total_growth=15
   → 植物の高さ = [15-0=15, 15-15=0]
4. 高さ10以上収穫: threshold=15-10=5
   → plants=[0,15]でthreshold=5以下は[0]
   → 1個収穫、plants=[15]
5. 20日経過: plants=[15], total_growth=35
   → 植物の高さ = 35-15 = 20
6. 高さ20以上収穫: threshold=35-20=15
   → plants=[15]でthreshold=15以下は[15]
   → 1個収穫
*/