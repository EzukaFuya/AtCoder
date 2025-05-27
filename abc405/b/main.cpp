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
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    int counter = 0;
    while(A.empty() == false) {
        set<int> S;
        for (int i = 0; i < A.size(); i++) {
            S.insert(A[i]);
        }
        bool ok = true;
        for (int i = 1; i <= M; i++) {
            if (S.find(i) == S.end()) {
                ok = false;
                break;
            }
        }
        if (ok == true) {
            A.pop_back();
            counter++;
        }
        else {
            cout << counter << endl;
            return 0;
        }
    }
    cout << counter << endl;
    return 0;
}
