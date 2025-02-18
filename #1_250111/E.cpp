#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool check(int K, const vector<int>& A, int N) {
    for(int i = 0; i < K; i++) {
        if(A[i] * 2 > A[N - K + i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    
    int left = 0;
    int right = N/2 + 1;
    
    while(right - left > 1) {
        int mid = (left + right) / 2;
        if(check(mid, A, N)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    cout << left << endl;
    return 0;
}