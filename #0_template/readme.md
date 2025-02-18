# C++ 競技プログラミングチートシート

## 入出力の高速化
```cpp
// 入出力の高速化
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

## 主要コンテナの使い方

### string
```cpp
string s = "hello";
s += " world";              // 文字列の結合
s.length(), s.size();      // 文字列の長さ
s.substr(2, 3);            // 部分文字列（開始位置, 長さ）
s.find("lo");              // 部分文字列の検索
s.replace(0, 2, "hi");     // 置換（開始位置, 長さ, 新しい文字列）

// 文字列から数値への変換
int n = stoi("123");       // string → int
long long ll = stoll("123"); // string → long long
double d = stod("3.14");   // string → double

// 数値から文字列への変換
string s = to_string(123); // 数値 → string
```

### map
```cpp
map<string, int> mp;       // キーでソートされた連想配列
mp["apple"] = 5;          // 要素の追加・更新
mp.erase("apple");        // 要素の削除

// 要素の存在確認
if (mp.count("apple")) { /* exists */ }
auto it = mp.find("apple");
if (it != mp.end()) { /* exists */ }

// イテレーション
for (const auto& [key, value] : mp) {
    cout << key << ": " << value << endl;
}

// 挿入の成功判定
auto [it, inserted] = mp.insert({"banana", 3});
```

### unordered_map
```cpp
unordered_map<string, int> ump;  // ハッシュテーブル（順序なし）
// 基本的な操作はmapと同じ
// 検索：O(1), ソートなし
```

### set/multiset
```cpp
set<int> st;              // 重複を許さない順序付き集合
st.insert(x);             // 要素の追加
st.erase(x);             // 要素の削除
st.count(x);             // xの個数（0か1）

multiset<int> mst;        // 重複を許す順序付き集合
mst.insert(x);           // 要素の追加
mst.erase(mst.find(x));  // 特定の要素を1つ削除
mst.erase(x);            // xをすべて削除

// 最大値・最小値
auto it = st.begin();     // 最小値
auto it = st.rbegin();    // 最大値
```

### deque
```cpp
deque<int> dq;           // 両端キュー
dq.push_front(x);        // 先頭に追加
dq.push_back(x);         // 末尾に追加
dq.pop_front();          // 先頭を削除
dq.pop_back();          // 末尾を削除
dq[i];                  // インデックスでのアクセス
```

## 頻出データ構造

### vector
```cpp
vector<int> vec;               // 動的配列の宣言
vector<int> vec(N);           // サイズNで初期化
vector<int> vec(N, value);    // サイズNでvalueで初期化
vector<vector<int>> vec(N, vector<int>(M));  // N×M の2次元配列

// 要素の追加と削除
vec.push_back(x);             // 末尾に追加
vec.pop_back();              // 末尾を削除

// 要素へのアクセス
vec[i];                      // i番目の要素
vec.front();                 // 先頭要素
vec.back();                  // 末尾要素

// サイズ関連
vec.size();                  // 要素数
vec.empty();                 // 空かどうか
vec.clear();                 // 全要素削除
```

### pair/tuple
```cpp
pair<int, int> p = {1, 2};
int x = p.first;            // 1番目の要素
int y = p.second;          // 2番目の要素

tuple<int, string, double> t = {1, "hello", 3.14};
get<0>(t);                 // 1番目の要素
```

### queue/priority_queue
```cpp
queue<int> q;
q.push(x);                 // 要素の追加
q.pop();                   // 先頭要素の削除
q.front();                // 先頭要素の参照

priority_queue<int> pq;                      // 最大値が先頭
priority_queue<int, vector<int>, greater<int>> pq;  // 最小値が先頭
```

## グラフアルゴリズム

### DFS (深さ優先探索)
```cpp
void dfs(vector<vector<int>>& graph, int v, vector<bool>& visited) {
    visited[v] = true;
    for (int next_v : graph[v]) {
        if (!visited[next_v]) {
            dfs(graph, next_v, visited);
        }
    }
}
```

### BFS (幅優先探索)
```cpp
void bfs(vector<vector<int>>& graph, int start) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        for (int next_v : graph[v]) {
            if (!visited[next_v]) {
                visited[next_v] = true;
                q.push(next_v);
            }
        }
    }
}
```

## 動的計画法（DP）テンプレート

### 1次元DP
```cpp
vector<int> dp(N + 1, 0);  // dp配列の初期化
dp[0] = 1;                 // 初期条件の設定

for (int i = 1; i <= N; i++) {
    // dp[i] の更新
}
```

### 2次元DP
```cpp
vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));
dp[0][0] = 1;  // 初期条件

for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= M; j++) {
        // dp[i][j] の更新
    }
}
```

## 二分探索
```cpp
// lower_bound: x以上の最初の要素のイテレータ
auto it = lower_bound(vec.begin(), vec.end(), x);
int pos = it - vec.begin();  // インデックスを取得

// upper_bound: xより大きい最初の要素のイテレータ
auto it = upper_bound(vec.begin(), vec.end(), x);

// 値の存在確認
bool exists = binary_search(vec.begin(), vec.end(), x);
```

## その他の有用なアルゴリズム

### 最大公約数 (GCD)
```cpp
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```

### 素数判定
```cpp
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

### エラトステネスの篩
```cpp
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}
```

### 順列・組み合わせ
```cpp
// 次の順列
next_permutation(vec.begin(), vec.end());

// 組み合わせ計算
long long C(int n, int r) {
    if (r > n) return 0;
    long long res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}
```

## デバッグ用
```cpp
// vectorの出力
template<typename T>
void print_vector(const vector<T>& vec) {
    for (const auto& x : vec) cout << x << " ";
    cout << endl;
}

// デバッグ出力
#define debug(x) cerr << #x << ": " << x << endl
```

## 定数
```cpp
const int MOD = 1000000007;
const int INF = 1e9;
const long long LINF = 1e18;
const double PI = acos(-1);
```

# C++ 標準ライブラリ関数チートシート

## 文字列操作 (<string>, <cctype>)
```cpp
// 文字の変換
tolower(c);      // 小文字に変換
toupper(c);      // 大文字に変換
isalpha(c);      // アルファベットかどうか
isdigit(c);      // 数字かどうか
isalnum(c);      // アルファベットまたは数字かどうか
isspace(c);      // 空白文字かどうか
ispunct(c);      // 句読点かどうか

// 文字列操作
s.substr(pos, len);     // 部分文字列の取得
s.find("abc");         // 部分文字列の検索
s.replace(pos, len, "new");  // 文字列の置換
stoi(str);      // 文字列→整数
to_string(val); // 数値→文字列
```

## アルゴリズム (<algorithm>)
```cpp
// ソートと検索
sort(v.begin(), v.end());  // ソート（昇順）
sort(v.begin(), v.end(), greater<int>());  // ソート（降順）
reverse(v.begin(), v.end());  // 要素の反転
binary_search(v.begin(), v.end(), x);  // 二分探索
lower_bound(v.begin(), v.end(), x);    // x以上の最初の要素
upper_bound(v.begin(), v.end(), x);    // xより大きい最初の要素

// 要素の操作
swap(a, b);      // 値の交換
min(a, b);       // 最小値
max(a, b);       // 最大値
min_element(v.begin(), v.end());  // 最小要素のイテレータ
max_element(v.begin(), v.end());  // 最大要素のイテレータ

// 要素のカウントと検索
count(v.begin(), v.end(), x);  // xの個数
find(v.begin(), v.end(), x);   // xの検索
unique(v.begin(), v.end());    // 重複要素の削除
```

## 数値操作 (<cmath>)
```cpp
abs(x);       // 絶対値
pow(x, y);    // xのy乗
sqrt(x);      // 平方根
ceil(x);      // 切り上げ
floor(x);     // 切り捨て
round(x);     // 四捨五入
```

## イテレータ操作
```cpp
next(it);      // 次のイテレータ
prev(it);      // 前のイテレータ
advance(it, n); // イテレータをn個進める
distance(it1, it2); // イテレータ間の距離
```

## 乱数生成 (<random>)
```cpp
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 6);  // 1から6までの乱数
int random_num = dis(gen);
```

## メモリ操作
```cpp
memset(arr, 0, sizeof(arr));  // 配列の初期化
memcpy(dest, src, size);      // メモリのコピー
```

## その他の便利な関数
```cpp
// 最大・最小
INT_MAX;        // int型の最大値
INT_MIN;        // int型の最小値
LLONG_MAX;      // long long型の最大値
LLONG_MIN;      // long long型の最小値

// ビット操作
__builtin_popcount(x);     // 1ビットの数
__builtin_clz(x);         // 先頭の0の数
__builtin_ctz(x);         // 末尾の0の数
```

## コンテナの便利なメンバ関数
```cpp
// vector
v.push_back(x);    // 末尾に追加
v.pop_back();      // 末尾を削除
v.front();         // 先頭要素
v.back();          // 末尾要素
v.empty();         // 空かどうか
v.size();          // サイズ
v.clear();         // 全要素削除

// set/map
s.insert(x);       // 要素の追加
s.erase(x);        // 要素の削除
s.count(x);        // 要素の個数
s.find(x);         // 要素の検索
```