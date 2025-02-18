#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    // 高速化のための設定
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int N;
    cin >> N;

    vector<long long int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    long long int count = 0;
    for (int i = 0; i < N; i++) {
        long long int B = A[i] / 2;
        count += upper_bound(A.begin(), A.end(), B) - A.begin();
    }

    cout << count << endl;
    
    return 0;
}