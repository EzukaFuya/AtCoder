#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 正方形が円内に完全に含まれているか判定する関数
bool isInCircle(ll x, ll y, ll radius) {
   // 正方形の4頂点がすべて円内にあるかを判定
   // (2x±1)^2 + (2y±1)^2 <= 4R^2 を判定
   return (2 * x + 1) * (2 * x + 1) + (2 * y + 1) * (2 * y + 1) <= 4 * radius * radius;
}

int main() {
   ll r;
   cin >> r;
   
   // 座標軸上の点をカウント
   ll result = (r - 1) * 4 + 1; // x軸上の点 + y軸上の点 + 原点
   
   // 第1象限の内部の点をカウント
   ll count = 0;
   ll maxY = r - 1;  // y座標の上限
   
   // x=1から順に探索
   for(ll x = 1; isInCircle(x, 1, r); x++) {
       // 現在のxに対する有効なyの最大値を求める
       while(!isInCircle(x, maxY, r)) {
           maxY--;
       }
       count += maxY;  // x固定時のy座標の個数を加算
   }
   
   // 4象限分を加算
   result += count * 4;
   
   cout << result << endl;
   return 0;
}