#include <bits/stdc++.h>
using namespace std;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, X;
    cin >> N >> X;
    
    vector<int> S(N), C(N);
    vector<double> P(N);
    
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> C[i] >> P[i];
        P[i] /= 100.0; // 確率を0~1の範囲に変換
    }
    
    // DP配列の初期化: d[s][x] = 状態sで予算xの時の最大期待値
    vector<vector<double>> d(1 << N, vector<double>(X + 1, 0.0));
    
    // 各予算と各状態について計算
    for (int x = 0; x <= X; x++) {
        for (int s = 0; s < (1 << N); s++) {
            // 各問題について提出を試みる
            for (int i = 0; i < N; i++) {
                int xx = x - C[i]; // 提出後の残り予算
                int ss = s | (1 << i); // 正解した場合の新しい状態
                
                // 予算が足りない、または既に問題iが解けている場合はスキップ
                if (xx < 0 || s == ss) {
                    continue;
                }
                
                // 期待値の計算:
                // P[i]の確率で正解して得点S[i]を獲得し、状態ssに遷移
                // (1-P[i])の確率で不正解となり、得点は増えず状態sのまま
                double val = P[i] * (d[ss][xx] + S[i]) + (1 - P[i]) * d[s][xx];
                
                // 最大の期待値を更新
                d[s][x] = max(d[s][x], val);
            }
        }
    }
    
    // 全ての状態での最大期待値を求める
    double ans = 0.0;
    for (int s = 0; s < (1 << N); s++) {
        ans = max(ans, d[s][X]);
    }
    
    // 出力
    cout << fixed << setprecision(15) << ans << endl;
    
    return 0;
}