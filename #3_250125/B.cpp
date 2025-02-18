#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    bool ans = true;
    double rate = A[1]/A[0];
    for (int i = 2; i < N; i++) {
        double rate2 = A[i] / A[i - 1];
        if (rate != rate2) ans = false;
    }
    
    if (ans == true) cout << "Yes";
    else cout << "No";
    cout << endl;

    return 0;
}