#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    vector<long long> A(5);
    long long last;
    long long last_last;
    long long count = 0;

    for (int i = 0; i < 5; i++) {
        cin >> A[i];
    }
    
    last = A[0];
    for (int i = 1; i < 5; i++) {
        if (last > A[i]) {
            count++;
        }
        else {
            last = A[i];
        }
    }

    if (count == 1) cout << "Yes";
    else cout << "No";
    cout << endl;

    return 0;
}