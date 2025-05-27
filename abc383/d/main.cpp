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

    // count the number of 9 divisors less than or equal to N
    // maximum number of a^2 * b^2 < N
    // a*b < sqrt(N) < 10^6
    // both a, b are prime numbers
    // 2 <= a, b <= 10^6 / 2
    // how do I count the number of prime numbers less than or equal to 10^6 / 2
    // Sieve of Eratosthenes
    vector<bool> is_prime(2e6, true);
    vector<ll> primes;
    is_prime[0] = false;
    is_prime[1] = false;

    int sqrt_N = sqrt(N);

    for (ll i = 2; i <= sqrt_N; i++) {
        if (is_prime[i]) {
            for (ll j = i * 2; j <= sqrt_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 0; i <= sqrt_N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    
    ll count = 0;
    ll left = 0;
    ll right = primes.size() - 1;
    while (left <= right) {
        ll a = primes[left];
        ll b = primes[right];
        if (a * b > sqrt_N) {
            right--;
        } else {
            count += right - left;
            left++;
        }
    }

    if (sqrt_N > 1) {
        int sqrt_N2 = sqrt(sqrt_N); //4th root of N
        if (sqrt_N2 > 1) {
            int sqrt_N3 = sqrt(sqrt_N2); //8th root of N
            for (int i = 0; i < sqrt_N3; i++) {
                ll a = primes[i];
                if (a > sqrt_N3) break;
                count++;
            }
        }
    }
    
    cout << count << endl;

    return 0;
}
