// 私のバージョンと比較したシンプルな解法
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    long long D;
    cin >> N >> M >> D;
    
    vector<long long> A(N), B(M);
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < M; i++) cin >> B[i];
    
    // ソート
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    while(true) {
        // 探索する要素がなくなったら終了
        if(N == 0 || M == 0) {
            cout << -1 << endl;
            return 0;
        }
        
        // 両方の配列の最大値を取得
        long long x = A.back();
        long long y = B.back();
        
        // 差がD以下なら答えを出力
        if(abs(x - y) <= D) {
            cout << (x + y) << endl;
            return 0;
        }
        
        // 大きい方の要素を削除
        if(x > y) {
            A.pop_back();
            N--;
        } else {
            B.pop_back();
            M--;
        }
    }
    
    return 0;
}