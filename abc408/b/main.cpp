#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    set<int> A;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        A.insert(num);
    }

    cout << A.size() << endl;
    int counter = 0;
    for (auto itr = A.begin(); itr != A.end(); itr++) {
        if (itr != A.begin()) cout << " ";
        cout << *itr;
    }
    cout << endl;
    return 0;
}