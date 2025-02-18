#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N), Q(N);
    vector<int> person_with_number(N + 1);
    
    // 入力
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> Q[i];
        person_with_number[Q[i]] = i + 1;
    }

    for (int i = 1; i <= N; i++) {
        int person = person_with_number[i]; 
        int watching = P[person - 1];
        cout << Q[watching - 1];
        if (i != N) cout << " ";
    }
    cout << endl;

    return 0;
}