#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> H(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    int max_counter = 1;
    for (int i = 0; i < N; i++) {
        int height = H[i];
        for (int j = 1; j < N; j++) {
            int counter = 0;
            while (1) {
                counter++;
                int itr = i + j * counter;
                if (itr >= N) break;
                else if (H[itr] != height) break;
            }
            max_counter = max(max_counter, counter);
        }
    }
    cout <<max_counter << endl;
    return 0;
}