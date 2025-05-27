#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<set<int>> user_contest(N + 1);
    vector<set<int>> contest_user(M + 1);
    vector<bool> is_all_contest(N + 1, false);

    for (int i = 0; i < Q; i++) {
        int que;
        cin >> que;
        if (que == 1) {
            int X, Y;
            cin >> X >> Y;
            contest_user[Y].insert(X);
            user_contest[X].insert(Y);
        }
        else if (que == 2) {
            int X;
            cin >> X;
            is_all_contest[X] = true;
        }
        else if (que == 3) {
            int x, y;
            cin >> x >> y;
            if (is_all_contest[x] == true) {
                cout << "Yes" << endl;
            } else if( contest_user[y].count(x)) {
                cout << "Yes" << endl;
            }
             else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}