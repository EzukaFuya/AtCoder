#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    // 高速化のための設定
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int N, D;
    cin >> N >> D;

    vector<int> T(N);
    vector<int> L(N);
    vector<int> MAX_snake(D);
    int max = 0;
    for (int i = 0; i < N; i++) {
        cin >> T[i] >> L[i];
        for (int j = 1; j <= D; j++) {
            MAX_snake[j-1] = std::max(MAX_snake[j-1], T[i] * (L[i] + j));
        }
    }

    for (int i = 0; i < D; i++) {
        cout << MAX_snake[i] << endl;
    }
    
    return 0;
}