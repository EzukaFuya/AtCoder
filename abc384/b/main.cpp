#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;
    
    for (int i = 0; i < N; i++) {
        int div, rate;
        cin >> div >> rate;

        if (div == 1 && 1600 <= R && R <= 2799) {
            R += rate;
        }
        else if (div == 2 && 1200 <= R && R <= 2399) {
            R += rate;
        }
    }

    cout << R << endl;
    return 0;
}