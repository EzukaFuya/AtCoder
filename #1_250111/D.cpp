#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    // 入力
    int N;
    cin >> N;
    
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<int> C(N, 0);
    vector<int> D(N+1, 0);
    for (int i = 0; i < N; i++) {
        int get_stone = 0, loss_stone = 0;
        if (i > 0) {
            C[i] = C[i - 1] + D[i];
            get_stone = C[i];
        }
        A[i] += get_stone;

        loss_stone = min(A[i], N - (i + 1));
        D[i + 1]++;
        D[min(N, i + loss_stone + 1)]--;
        A[i] -= loss_stone;
    }

    for (int i = 0; i < N; i++) {
        cout << A[i] << (i == N-1 ? "\n" : " ");
    }
}