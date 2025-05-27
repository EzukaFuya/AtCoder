#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> pigeon_to_nest(N); // pigeon_to_nest[pigeon] = nest
    vector<int> nest_to_label(N); // nest_to_label[nest] = label
    vector<int> label_to_nest(N); // label_to_nest[label] = nest

    for (int i = 0; i < N; i++) {
        pigeon_to_nest[i] = i; // initially, each pigeon is in its own nest
        nest_to_label[i] = i; // initially, each nest has its own label
        label_to_nest[i] = i; // initially, each label corresponds to its own nest
    }

    for (int i = 0; i < Q; i++) {
        int q, a, b;
        cin >> q;
        if (q == 1) {
            cin >> a >> b;
            a--;
            b--;
            pigeon_to_nest[a] = label_to_nest[b];

        }
        else if (q == 2) {
            cin >> a >> b;
            a--;
            b--;
            swap(label_to_nest[a], label_to_nest[b]);
            swap(nest_to_label[label_to_nest[a]], nest_to_label[label_to_nest[b]]);
        } else if (q == 3) {
            cin >> a;
            a--;
            int nest = pigeon_to_nest[a];
            int label = nest_to_label[nest];
            cout << label + 1 << endl; // output the label of the nest where pigeon a is located
        } 

    }
    return 0;
}
