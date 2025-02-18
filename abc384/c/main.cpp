#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;

    vector<pair<int, string>> score;  // {sum, name_string}のペアに変更
    vector<int> point = {a, b, c, d, e};
    vector<char> name = {'A', 'B', 'C', 'D', 'E'};
    
    int n = 5;

    for (int bit = 1; bit < (1 << n); bit++) {
        int sum = 0;
        string names = "";  // ビット列を直接文字列に変換
        for (int i = 0; i < n; i++) {
            if (bit & (1 << i)) {
                sum += point[i];
                names += name[i];
            }
        }
        score.push_back({sum, names});
    }

    sort(score.begin(), score.end(), [](const pair<int,string>& a, const pair<int,string>& b) {
        if(a.first != b.first) return a.first > b.first;  // sumで降順
        return a.second < b.second;  // sumが同じ場合は文字列で辞書順
    });

    for (const auto& p : score) {
        cout << p.second << endl;
    }

    return 0;
}