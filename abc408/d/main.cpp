#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> cost_zero_one(n+1, 0);
        for (int i = 0; i < n; i++) {
            cost_zero_one[i + 1] = cost_zero_one[i] + (s[i] == '0' ? 1 : -1);
        }

        int cost_left = 0;
        int cost_min = 0;
        for (int i = 0; i <= n; i++) {
            cost_min = min(cost_min, cost_zero_one[i] - cost_left);
            cost_left = max(cost_left, cost_zero_one[i]);
        }

        int sum = count(s.begin(), s.end(), '1');

        cout << sum + cost_min << endl;
    }
    
    return 0;
}
