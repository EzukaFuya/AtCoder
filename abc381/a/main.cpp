#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, str, mid, end;
    cin >> N;
    str = 0;
    mid = (N-1)/2;
    end = N;

    string S;
    cin >> S;

    if (N % 2 == 0) {
        cout << "No" << endl;
        return 0;
    }

    for (int i = str; i < mid; i++) {
        if (S[i] != '1') {
            cout << "No" <<endl;
            return 0;
        }
    }

    if (S[mid] != '/') {
        cout << "No" <<endl;
        return 0;
    }

    for (int i = mid + 1; i < end; i++) {
        if (S[i] != '2') {
            cout << "No" <<endl;
            return 0;
        }
    }

    cout << "Yes" <<endl;
    

    return 0;
}