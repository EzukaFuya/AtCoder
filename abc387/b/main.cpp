#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

int main() {
    int X;
    cin >> X;

    int all = 2025;
    multiset<int> qq;
    

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            qq.insert(i * j);
        }
    }

    int ans = all - X * qq.count(X);
    cout << ans << endl;
    return 0;
}