#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >>M;

    vector<int> A(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i];
    }

    int counter = 0;
    vector<int> B;
    for (int key = 1; key <= N; key++) {
        if (count(A.begin(), A.end(), key) == 0) {
            B.push_back(key);
            counter++;
        }
    }
    cout << counter << endl;
    for (int j = 0; j < B.size(); j++) {
        cout << B[j];
        if (j != B.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}