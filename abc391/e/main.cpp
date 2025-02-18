#include <bits/stdc++.h>
using namespace std;

pair<char, int> f(string& A, int l, int r) {
    if (l + 1 == r) {
        return {A[l], 1};
    }
    
    int m1 = (2 * l + r) / 3;
    int m2 = (l + 2 * r) / 3;
    
    auto [val1, cnt1] = f(A, l, m1);
    auto [val2, cnt2] = f(A, m1, m2);
    auto [val3, cnt3] = f(A, m2, r);
    
    if (val1 == val2 && val2 == val3) {
        vector<int> cnts = {cnt1, cnt2, cnt3};
        sort(cnts.begin(), cnts.end());
        return {val1, cnt1 + cnt2 + cnt3 - cnts[2]};
    }
    else if (val1 == val2) return {val1, min(cnt1, cnt2)};
    else if (val1 == val3) return {val1, min(cnt1, cnt3)};
    else if (val2 == val3) return {val2, min(cnt2, cnt3)};
    
    return {val1, cnt1};
}

int main() {
    int N;
    cin >> N;
    string A;
    cin >> A;
    
    cout << f(A, 0, pow(3, N)).second << endl;
    
    return 0;
}