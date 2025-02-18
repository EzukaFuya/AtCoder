#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> card;
    for (int i = 0; i < 4; i++) {
        int A;
        cin >> A;
        card.insert(A);
    }

    if (card.size() == 2) cout << "Yes";
    else cout << "No";
    cout << endl;
    
    return 0;
}