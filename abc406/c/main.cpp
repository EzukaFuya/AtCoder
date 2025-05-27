#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    vector<pair<char,ll>> peak_vec;
    for (int i = 1; i < N; i++) {
        // ascending
        if (P[i] > P[i - 1]) {
            if (peak_vec.empty() || peak_vec.back().first == '>') {
                peak_vec.push_back(make_pair('<', 1));
            }
            else {
                peak_vec.back().second++;
            }
        }
        // descending 
        if (P[i] < P[i -1]) {
            if (peak_vec.empty() || peak_vec.back().first == '<') {
                peak_vec.push_back(make_pair('>', 1));
            }
            else {
                peak_vec.back().second++;
            }
        }
    }

    ll answer = 0;
    for (int i = 1; i < peak_vec.size() - 1; i++) {
        if (peak_vec[i].first == '>') {
            answer += peak_vec[i-1].second * peak_vec[i+1].second;
        }
    }
    cout << answer << endl;
    return 0;
}
