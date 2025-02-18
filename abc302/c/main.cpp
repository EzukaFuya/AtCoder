#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calc_diff(string& str1, string& str2) {
    int diff = 0;
    for(int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) diff++;
    }
    return diff;
}

bool dfs(int v, int cnt, vector<bool>& used, vector<vector<int> >& adj) {
    if (cnt == used.size()) return true;
    
    for (int next : adj[v]) {
        if (!used[next]) {
            used[next] = true;
            if (dfs(next, cnt + 1, used, adj)) return true;
            used[next] = false;
        }
    }
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    vector<vector<int>> adj(N);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (calc_diff(S[i], S[j]) == 1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        vector<bool> used(N);
        used[i] = true;
        if (dfs(i, 1, used, adj)) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
    return 0;
}