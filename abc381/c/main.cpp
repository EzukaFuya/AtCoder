#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;
    cin >> N >> S;

    queue<int> que; // index of '/'
    for (int i = 0; i < N; i++) {
        if (S[i] == '/') que.push(i);
    }

    int size = 0;
    while (!que.empty()) {
        int num = que.front();
        que.pop();

        int left = num - 1;
        int right = num + 1;
        
        while (left >= 0 && right < N) {
            if (S[left] != '1') break;
            if (S[right] != '2') break;
            left--;
            right++;
        }
        size = max(size, right - left - 1);        
    }
    cout << size << endl;
    return 0;
}
