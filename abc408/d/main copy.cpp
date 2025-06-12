#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        string S;
        cin >> N >> S;
      
        int total_ones = 0;
        for (char c : S) {
            if (c == '1') total_ones++;
        }
        
        int min_ops = total_ones;
        
        int i = 0;
        while (i < N) {
            if (S[i] == '1') {
                int start = i;
                while (i < N && S[i] == '1') {
                    i++;
                }
                int length = i - start;
                
                int ops = total_ones - length;
                min_ops = min(min_ops, ops);
            } else {
                i++;
            }
        }
        
        cout << min_ops << "\n";
    }
    
    return 0;
}
