#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;
const int MAXN = 4e6 + 5;  // 最大値に対応

vector<long long> factorial(MAXN);
vector<long long> invFactorial(MAXN);

// 高速累乗計算（a^b % MOD）
long long power(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

// 階乗と逆元の前計算
void precompute() {
    factorial[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    
    invFactorial[MAXN - 1] = power(factorial[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        invFactorial[i] = (invFactorial[i + 1] * (i + 1)) % MOD;
    }
}

// 多項係数 (n choose k1,k2,...,km) % MOD の計算
long long multinomial(int n, vector<int> k) {
    long long res = factorial[n];
    for (int ki : k) {
        res = (res * invFactorial[ki]) % MOD;
    }
    return res;
}

int main() {
    precompute();
    
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    
    // 可能な並べ方のパターン
    // 1. リンゴ→オレンジ→バナナ→ブドウ
    long long pattern1 = multinomial(A + B + C + D, {A, B, C, D});
    
    // 2. リンゴ→バナナ→オレンジ→ブドウ
    long long pattern2 = multinomial(A + B + C + D, {A, C, B, D});
    
    // 3. オレンジ→リンゴ→バナナ→ブドウ
    long long pattern3 = multinomial(A + B + C + D, {B, A, C, D});
    
    // 4. リンゴ→オレンジ→ブドウ→バナナ
    long long pattern4 = multinomial(A + B + C + D, {A, B, D, C});
    
    // 5. オレンジ→リンゴ→ブドウ→バナナ
    long long pattern5 = multinomial(A + B + C + D, {B, A, D, C});
    
    // 結果を合計して998244353で割った余りを求める
    long long result = (((pattern1 + pattern2) % MOD + pattern3) % MOD + pattern4) % MOD;
    result = (result + pattern5) % MOD;
    
    cout << result << endl;
    
    return 0;
}