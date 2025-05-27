#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string T, S;
    cin >> T >> S;

    int size_T = T.size(), size_S = S.size();
    int counter = 0;

    for (int i = 0; i < size_T - size_S + 1; i++) {
        int counter = 0;
        for (int j = i; j < size_S + i; j++) {
            if (T[j] == '?' && T[j] != S[j - i]) {
                counter++;
            }
            else if (T[j] != S[j - i]) {
                counter = 1000;
                break;
            }
        }
        if (counter <= 4) {
            cout << "Yes" << endl;
            return 0;   
        }
    }
    cout << "No" << endl;
    
    return 0;
}