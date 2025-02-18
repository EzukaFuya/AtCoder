#include <bits/stdc++.h>
using namespace std;

// 型の短縮
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;

// マクロ
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep2(i, s, n) for (int i = (s); i < (int)(n); i++)
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

// 定数
const int INF = 1001001001;
const ll LINF = 1001001001001001001ll;
const int MOD = 1000000007;
const double PI = acos(-1);

// デバッグ用マクロ
#ifdef LOCAL
#define debug(x) cerr << #x << ": " << x << endl
#else
#define debug(x)
#endif

// 多次元vectorの初期化
template<typename T>
vector<T> make_vec(size_t a){
    return vector<T>(a);
}
template<typename T, typename... Ts>
auto make_vec(size_t a, Ts... ts){
    return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}

// 数値関連の関数
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// メイン関数
int main() {
    // 入出力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 小数点以下の出力桁数の設定
    cout << fixed << setprecision(15);
    
    // ここにメインの処理を書く
    
    return 0;
}