#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    vector<int> B(M);

    cin >> A[0];
    for (int i = 1;i < N; i++) {
        int a;
        cin >> a;
        A[i] = min(a, A[i-1]);
    }

    for (int i = 0; i < M; i++) {
        cin >> B[i];
    }

    for (int i = 0; i < M; i++) {
        auto iter = lower_bound(A.begin(), A.end(), B[i], greater<int>());
        if(iter == A.end()) {
            cout << -1 <<endl;
            continue;
        }
        cout << iter - A.begin()+1 <<endl;
    }

    return 0;
}
