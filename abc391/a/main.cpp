#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string C;
    cin >> C;

    if (C == "N") cout << "S";
    if (C == "E") cout << "W";
    if (C == "W") cout << "E";
    if (C == "S") cout << "N";
    if (C == "NE") cout << "SW";
    if (C == "NW") cout << "SE";
    if (C == "SE") cout << "NW";
    if (C == "SW") cout << "NE";
    cout << endl;

    return 0;
}