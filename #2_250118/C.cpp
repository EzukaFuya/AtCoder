#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int Q;
    cin >> Q;

    vector<long long> snakes;
    int itr = 0;
    long long snake_head = 0;
    snakes.push_back(snake_head);

    for (int i = 0; i < Q; i++) {
        int query;
        cin >> query;
        if (query == 1) {
            int l;
            cin >> l;
            snake_head += l;
            snakes.push_back(snake_head);
        }
        else if (query == 2) {
            itr++;
        }
        else if (query == 3) {
            int k;
            cin >> k;
            cout << snakes[k -1 + itr] - snakes[itr] << endl;
        }
    }
    return 0;
}