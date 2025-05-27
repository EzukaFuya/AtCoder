#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> food(M);
    for (int i = 0; i < M; i++) {
        int K;
        cin >> K;
        food[i].resize(K);
        for (int j = 0; j < K; j++) {
            cin >> food[i][j];
        }
    }
    
    vector<vector<int>> ingredient(N+1);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < food[i].size(); j++) {
            ingredient[food[i][j]].push_back(i);
        }
    }

    vector<int> likefood(N);
    for (int i = 0; i < N; i++) {
        cin >> likefood[i];
    }

    int counter = 0;
    vector<int> dislike_count(M);
    vector<bool> dislike_food_count(M, false);
    for (int i = 0; i < M; i++) {
        dislike_count[i] = food[i].size();
    }

    for (int i = 0; i < N; i++) {

        for (int food : ingredient[likefood[i]]) {
            if (!dislike_food_count[food]) {
                dislike_count[food]--;

                if (dislike_count[food] == 0) {
                    counter++;
                    dislike_food_count[food] = true;
                }
            }
        }
        cout << counter << endl;
    }

    return 0;
}