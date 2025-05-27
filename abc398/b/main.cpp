#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<int, int> A;
    for (int i = 0; i < 7; i++) {
        int a;
        cin >> a;
        A[a]++;
    }

    int bool_three = 0;
    int bool_two = 0;   

    for (const auto& pair : A) {
        if (pair.second >= 3) {
            bool_three++;
        }
        else if (pair.second == 2) {
            bool_two++;
        }
    }

    if (bool_three == 2) {
        cout << "Yes" << endl;
    }
    else if (bool_three == 1 && bool_two == 2) {
        cout << "Yes" << endl;
    }
    else if (bool_three == 1 && bool_two == 1) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }

    return 0;
}