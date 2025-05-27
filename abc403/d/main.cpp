#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, D;
    cin >> N >> D;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    int left = 0, right = 0;
    ll counter = 0;
    set<int> skip_num;

    map<int, int> A_map;
    for (int i = 0; i < N; i++) {
        A_map[A[i]]++;
    }

    if (D == 0) {
        ll counter = 0;
        for (auto pair : A_map) {
            counter += (--pair.second);
        }
        cout << counter << endl;
        return 0;
    }

    while (right < N) {
        if (skip_num.count(left)) {
            left++;
            continue;
        }
        else if (A[right] - A[left] == D) {
            counter ++;
            skip_num.insert(right);
            right++;
            left++;
        } else if (A[right] - A[left] < D) {
            right++;
        }
        else {
            left++;
        }
    }

    cout << counter << endl;
    return 0;
}