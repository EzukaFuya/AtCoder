#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }

    int a = H, b = -1, c = W, d = -1;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char blk = S[i][j];

            if (blk == '#') {
                a = min(a, j);
                b = max(b, j);
                c = min(c, i);
                d = max(d, i);
            }
        }
    }

    bool ans = true;

    if (0 <= a && a <= b && b <= W - 1 && 0 <= c && c <=d && d <=H - 1) {
        if (a == b && c == d) cout << "Yes" << endl;
        else {
            for (int i = c; i <= d; i++) {
                for (int j = a; j <= b; j++) {
                    char blk = S[i][j];
                    if (blk == '.') ans = false;
                }
            }
            
            if (ans == true) cout << "Yes";
            else cout << "No";
            cout << endl;
        }
    }
    else cout << "No" << endl;

    return 0;
}