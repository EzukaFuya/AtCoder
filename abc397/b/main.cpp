#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    string result = "";
    int counter = 0;

    for (int i = 0; i < S.length(); i++) {
        char exp = result.size() % 2 == 0 ? 'i' : 'o';

        if (S[i] == exp) {
            result += S[i];
        }
        else {
            result += exp;
            counter++;
            i--;
        }
    }

    if (result.size() % 2 == 1) {
        result += 'o';
        counter++;
    }

    cout << counter << endl;

    return 0;
}