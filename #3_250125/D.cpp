#include <iostream>
#include <unordered_set>
using namespace std;

int N;
long long A[12];      // 入力値の配列
long long group[12];  // 各グループの和
long long xor_val;    // グループ間のXOR結果
unordered_set<long long> results;  // 結果を格納するset

// idx: 現在の数字のindex
// group_count: 現在のグループ数
void dfs(int idx, int group_count) {
   for(int g = 0; g <= group_count; g++) {
       // 現在の値を一時的に除外
       xor_val ^= group[g];
       
       // 現在の数字をグループgに追加
       group[g] += A[idx];
       xor_val ^= group[g];
       
       if(idx == N-1) {
           // すべての数字を配置済み
           results.insert(xor_val);
       } else {
           if(g < group_count) {
               // 既存のグループに追加
               dfs(idx+1, group_count);
           } else {
               // 新しいグループを作成
               dfs(idx+1, group_count+1);
           }
       }
       
       // 状態を元に戻す
       xor_val ^= group[g];
       group[g] -= A[idx];
       xor_val ^= group[g];
   }
}

int main() {
   cin >> N;
   for(int i = 0; i < N; i++) cin >> A[i];
   
   dfs(0, 0);
   cout << results.size() << endl;
   return 0;
}