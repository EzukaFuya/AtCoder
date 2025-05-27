#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    vector<string> X;
    vector<string> Y;

    for (int i = 0; i < Q; i++) {
        int T;
        string S;
        cin >> T;
        cin >> S;

        if (T == 1) {
            X.push_back(S);

            vector<int> erase_index;
            for (int j = 0; j < Y.size(); j++) {
                if (Y[j].size() >= S.size() && Y[j].substr(0, S.size()) == S) {
                    erase_index.push_back(j);
                }
            }

            for (int j = erase_index.size() - 1; j >= 0; j--) {
                Y.erase(Y.begin() + erase_index[j]);
            }   

        } else if (T == 2) {
            bool has_prefix = false;
            
            for (auto& prefix : X) {
                if (S.size() >= prefix.size() && S.substr(0, prefix.size()) == prefix) {
                    has_prefix = true;
                    break;
                }
            }
            
            if (!has_prefix) {
                Y.push_back(S);
            }
        }

        cout << Y.size() << endl;
        
    }
    return 0;
}