#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> pig(N);
    vector<int> freq(N + 1, 0);

    for (int i = 0; i < N; i++) {
        pig[i] = i + 1;
        freq[i + 1]++;
    }

    int sum_count = 0;
    for (int i = 0;i < Q; i++) {
        int q1;
        cin >> q1;

        if (q1 == 1) {
            int r1, r2;
            cin >> r1 >> r2;

            freq[pig[r1 - 1]]--;
            if (freq[pig[r1 - 1]] == 1) {
                sum_count--;
            }

            freq[r2]++;
            if (freq[r2] == 2) {
                sum_count++;
            }
            pig[r1 - 1] = r2;
        }

        else if(q1 == 2) {
            cout << sum_count << endl;
        }
    }

    return 0;
}