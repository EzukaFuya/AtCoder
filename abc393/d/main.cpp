#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string S;

    cin >> N;
    int counter = 0;
    vector<int> ones;
    for (int i = 0; i < N; i++){
        char s;
        cin >> s;
        if (s == '0') counter++;
        else if (s == '1') ones.push_back(counter);
    }

    vector<int> ones_copy = ones;

    int num1 = ones[ones.size()/2];
    int num2 = ones[(ones.size() + 2 - 1)/2];
    
    ll sum1 = 0;
    for (int i = 0; i < ones.size(); i++) {
        sum1 += abs(ones[i] - num1);
    }

    ll sum2 = 0;
    for (int i = 0; i < ones.size(); i++) {
        sum2 += abs(ones_copy[i] - num2);
    }

    cout << min(sum1, sum2) << endl;

    return 0;
}