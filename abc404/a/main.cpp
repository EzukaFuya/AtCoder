#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    set<char> S_abc;
    S_abc.insert('a');
    S_abc.insert('b');
    S_abc.insert('c');
    S_abc.insert('d');
    S_abc.insert('e');
    S_abc.insert('f');
    S_abc.insert('g');
    S_abc.insert('h');
    S_abc.insert('i');
    S_abc.insert('j');
    S_abc.insert('k');
    S_abc.insert('l');
    S_abc.insert('m');
    S_abc.insert('n');
    S_abc.insert('o');
    S_abc.insert('p');
    S_abc.insert('q');
    S_abc.insert('r');
    S_abc.insert('s');
    S_abc.insert('t');
    S_abc.insert('u');
    S_abc.insert('v');
    S_abc.insert('w');
    S_abc.insert('x');
    S_abc.insert('y');
    S_abc.insert('z');

    for (int i = 0; i < S.size(); i++) {
        S_abc.erase(S[i]);
    }

    cout << *S_abc.begin() << endl;

    return 0;
}
