#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<pair<pair<int ,int>, char>> points(M);
    for (int i = 0; i < M; i++) {
        int x, y;
        char c;
        cin >> x >> y >>c;
        points.push_back({{x, y}, c});
    }

    sort(points.begin(), points.end());

    int min_y = INT_MAX;
    bool possible = true;

    for (auto p : points) {
        if (p.second == 'W') {
            min_y = min(min_y, p.first.second);
        }
        else {
            if (min_y <= p.first.second) possible = false;
        }
    }

    if (possible)cout << "Yes";
    else cout << "No";
    cout << endl;
    
    return 0;
}