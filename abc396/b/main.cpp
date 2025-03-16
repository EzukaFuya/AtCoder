#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    stack<int> cards;
    for (int i = 0; i < 100; i++) {
        cards.push(0);
    }
    for (int i = 0; i < Q; i++) {
        int query;
        cin >> query;
        if (query == 1) {
            int x;
            cin >> x;
            cards.push(x);
        }
        else if (query == 2) {
            cout << cards.top() << endl;
            cards.pop();
        }
    }
    return 0;
}