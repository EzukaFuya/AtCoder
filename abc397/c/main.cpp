#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >>  N;

    vector<int> A(N);   
    vector<int> A_left(N);
    vector<int> A_right(N);
    set<int> A_set;

    for (int i = 0;i < N; i++) {
        int a;
        cin >> a;

        A[i] = a;   
        A_set.insert(a);
        A_left[i] = A_set.size();
    }

    A_set.clear();
    for (int i = N - 1; i >= 0; i--) {
        A_set.insert(A[i]);
        A_right[i] = A_set.size();
    }

    int max_count = 0;
    for (int i = 0; i < N - 1; i++) {
        max_count = max(max_count, A_left[i] + A_right[i + 1]);
    }

    cout << max_count << endl;

    return 0;
}