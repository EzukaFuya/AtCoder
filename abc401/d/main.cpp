#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    string S;
    cin >> S;

    string S3 = S;

    // replace all '?' adjacent to 'o' with '.'
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == '?') {
            if ((i > 0 && S[i-1] == 'o') || (i < S.size()-1 && S[i+1] == 'o')) {
                S[i] = '.';
            }
        }
    }

    int count_o = 0;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'o') {
            count_o++;
        }
    }

    // number of 'o' in S is equal to K
    if (count_o == K) {
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == '?') {
                S[i] = '.';
            }
        }
        cout << S << endl;
        return 0;
    }

    // copy string S to S2;
    string S2 = S;

    // replace maximum number of '?' with 'o'
    for (int i = 0; i < S.size(); i++) {
        if (i == 0 && S[i] == '?' && S[i + 1] != 'o') {
            S[i] = 'o';
            count_o++;
        }
        else if (i == S.size() - 1 && S[i] == '?' && S[i - 1] != 'o') {
            S[i] = 'o';
            count_o++;
        }
        else if (S[i] == '?' && S[i - 1] != 'o' && S[i + 1] != 'o') {
            S[i] = 'o';
            count_o++;
        }
    }

    if (count_o != K) {

        cout << S2 << endl;
        return 0;
    }

    // M = K の場合
    int i = 0;
    while (i < S2.size()) {
        if (S2[i] == '?') {
            int start = i;
            // 連続する'?'の長さを測定
            while (i < S2.size() && S2[i] == '?') i++;
            int length = i - start;
            
            // 奇数個の場合のみ処理
            if (length % 2 == 1) {
                for (int j = 0; j < length; j++) {
                    S2[start + j] = (j % 2 == 0) ? 'o' : '.';
                }
            }
            // 偶数個の場合は処理しない（'?'のまま）
        } else {
            i++;
        }
    }
    cout << S2 << endl;

    return 0;
}