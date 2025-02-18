#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (i != s.length() - 1 && s[i] == '0' && s[i + 1] == '0') {
            i++;
        }
        count++;
    }

    cout << count << endl;
    
    return 0;
}