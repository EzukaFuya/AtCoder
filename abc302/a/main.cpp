#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    long long A, B;
    cin >> A >> B;
    long long C;
    C = (long long)(A + B - 1)/ B;
    cout << C << endl;
    return 0;
}