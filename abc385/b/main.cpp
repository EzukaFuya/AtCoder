#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, X, Y;
    cin >> H >> W >> X >>Y;

    vector<string> S(H);
    vector<vector<bool>> visited(H, vector<bool> (W, false));
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    string T;
    cin >> T;

    int count = 0;
    X--;
    Y--;

    for (int i = 0; i < T.length(); i++) {
        char c = T[i];
        if (c == 'U') {
            if (S[X - 1][Y] == '.') {
                X--;
            }
            else if (S[X - 1][Y] == '@' ) {
                X--;
                if (visited[X][Y] == false) {
                    visited[X][Y] = true;
                    count++;
                }
            }
        }
        else if (c == 'D') {
            if (S[X + 1][Y] == '.') {
                X++;
            }
            else if (S[X + 1][Y] == '@' ) {
                X++;
                if (visited[X][Y] == false) {
                    visited[X][Y] = true;
                    count++;
                }
            }

        }
        else if (c == 'L') {
            if (S[X][Y - 1] == '.') {
                Y--;
            }
            else if (S[X][Y - 1] == '@' ) {
                Y--;
                if (visited[X][Y] == false) {
                    visited[X][Y] = true;
                    count++;
                }
            }
        }
        else if (c == 'R') {
            if (S[X][Y + 1] == '.') {
                Y++;
            }
            else if (S[X][Y + 1] == '@') {
                Y++;
                if (visited[X][Y] == false) {
                    visited[X][Y] = true;
                    count++;
                }
            }
        }
    }
    X++;
    Y++;
    cout << X <<" "<< Y << " " << count << endl;
    return 0;
}