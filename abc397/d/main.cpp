#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<pair<int, ll>>>;

int main() {
    // 入力の高速化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    vector<ll> divisors;
    for (ll i = 1; i * i * i <= N; i++) {
        if (N % i == 0) {
            divisors.push_back(i);
            if (i * i != N) divisors.push_back(N / i);
        }
    }

    for (int i = 0; i < divisors.size(); i++) {
        double a = 3.0;
        double b = 3.0 * divisors[i];
        double c = divisors[i] * divisors[i] - (double)N / divisors[i];
        double d = b * b - 4 * a * c;
        if (d < 0) continue;
        double dis_p = (-b + sqrt(d)) / (2 * a);
        double dis_m = (-b - sqrt(d)) / (2 * a); 
        
        ll y = round(dis_p);
        ll x = divisors[i] + y;
        if (x > 0 && y > 0) {
            if (x < y) swap(x, y);
            if (x*x*x - y*y*y == N) {
                cout << x << " " << y << endl;
                return 0;
            }
        }
        y = round(dis_m);
        x = divisors[i] + y;
        if (x > 0 && y > 0) {
            if (x < y) swap(x, y);
            if (x*x*x - y*y*y == N) {
                cout << x << " " << y << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl; 

    return 0;
}