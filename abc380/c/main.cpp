#include <bits/stdc++.h>
using namespace std;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    bool is_one = false;
    string Ones;
    string Zeros;
    string Ans;
    int One_count = 0;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        if (c == '1') {
            if (is_one == false) {
                One_count++;
                if (One_count != K && Zeros.empty() == false) {
                    Ans += Zeros;
                    Zeros.clear();
                }
            }
            is_one = true;
            Ones.push_back('1');
        }
        else {
            if (is_one == true) {
                if (Ones.empty() == false) {
                    Ans += Ones;
                    Ones.clear();
                }
            }
            is_one = false;
            Zeros.push_back('0');
        }
    }
    if (is_one == true) {
        Ans += Ones;
    }
    else {
        Ans += Zeros;
    }
    if (One_count == K) Ans += Zeros;

    cout << Ans << endl;
    return 0;
}