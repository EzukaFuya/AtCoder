#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> S(N);
    vector<string> T(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    // Compare S and T with 4 directions
    // 0: no rotation, 1: 90 degrees, 2: 180 degrees, 3: 270 degrees

    // 0 degrees 
    int counter = 0;
    int direction = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (S[i][j] != T[i][j]) {
                counter++;
            }
        }
    }
    direction = 1;

    // 90 degrees
    int counter_90 = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (S[i][j] != T[j][N - 1 - i]) {
                counter_90++;
            }
        }
    }
    if (counter_90 < counter) {
        counter = counter_90;
        direction = 2;
    }

    // 180 degrees
    int counter_180 = 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (S[i][j] != T[N - 1 - i][N - 1 - j]) {
                counter_180++;
            }
        }
    }
    if (counter_180 < counter) {
        counter = counter_180;
        direction = 3;
    }

    // 270 degrees
    int counter_270 = 3;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (S[i][j] != T[N - 1 - j][i]) {
                counter_270++;
            }
        }
    }
    if (counter_270 < counter) {
        counter = counter_270;
        direction = 4;
    }

    cout << counter << endl;


    return 0;
}