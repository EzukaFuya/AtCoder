#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    priority_queue<int> blacks;
    priority_queue<int> whites;
    for (int i = 0; i < N; i++) {
        int b;
        cin >> b;
        blacks.push(b);
    }
    for (int i = 0; i < M; i++) {
        int w;
        cin >> w;
        whites.push(w);
    }

    ll max_sum = 0;
    ll sum = 0;

    while (blacks.empty() == false && whites.empty() == false) {
        int black_val = blacks.top();
        int white_val = whites.top();
        if (black_val + white_val > black_val && black_val + white_val > 0) {
            max_sum += black_val;
            max_sum += white_val;
            blacks.pop();
            whites.pop();
        }
        else if (black_val > 0) {
            max_sum += black_val;
            blacks.pop();
            whites.pop();
        }
        else {
            break;
        }
    }
    while (blacks.empty() == false) {
        if (blacks.top() > 0) max_sum += blacks.top();
        blacks.pop();
    }
    cout << max_sum << endl;

    return 0;
}