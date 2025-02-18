#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 冪乗計算のヘルパー関数
ll power(ll base, ll exp) {
    ll result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// x以下のヘビ数をカウントする関数
ll countSnakeNumbers(ll x) {
    vector<int> digit;
    while (x > 0) {
        digit.push_back(x % 10);
        x /= 10;
    }
    reverse(digit.begin(), digit.end());

    int n = digit.size();
    ll result = 0;

    // 先頭が桁である場合
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            result++;
            break;
        }

        result += power(digit[0], n - i - 1) * min(digit[0], digit[i]);

        if (digit[i] >= digit[0]) break;
    }

    for (int i = 0; i < n; i++) {
        int max_digit = (i == 0) ? digit[0] - 1 : 9;
        for (int j = 1; j <= max_digit; j++) {
            result += power(j, n - 1 - i);
        }
    }

    return result;

}

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 入力
    ll L, R;
    cin >> L >> R;
    
    // 結果の計算
    ll answer = countSnakeNumbers(R) - countSnakeNumbers(L - 1);
    
    // 出力
    cout << answer << "\n";
    
    return 0;
}