#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double calc_similarity(const map<int, int>& map1, const map<int, int>& map2, int sum1, int sum2) {
    double similarity = 0.0;
    
    // map1の各要素について
    for (const auto& [key, value1] : map1) {
        // map2に同じキーが存在する場合
        if (map2.count(key)) {
            // それぞれの割合を計算して掛け合わせる
            double ratio1 = static_cast<double>(value1) / sum1;
            double ratio2 = static_cast<double>(map2.at(key)) / sum2;
            similarity += ratio1 * ratio2;
        }
    }
    
    return similarity;
}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> K(N);
    vector<map<int, int>> A(N);

    for (int i = 0; i < N; i++) {
        cin >> K[i];
        for (int j = 0; j < K[i]; j++) {
            int a;
            cin >> a;
            A[i][a]++;
        }
    }

    double max_rate = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double rate;
            rate = calc_similarity(A[i], A[j], K[i], K[j]);
            if (rate > max_rate) max_rate = rate;
        }
    }
    printf("%.15f\n", max_rate);

    return 0;
}