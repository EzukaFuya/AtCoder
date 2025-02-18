#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read basic parameters
    int num_houses, num_movements;
    ll santa_x, santa_y;
    cin >> num_houses >> num_movements >> santa_x >> santa_y;
    
    // Maps to store houses coordinates
    // house_by_x[x] contains all y-coordinates of houses at x
    // house_by_y[y] contains all x-coordinates of houses at y
    map<ll, set<ll>> house_by_x;
    map<ll, set<ll>> house_by_y;
    
    // Read house coordinates
    for(int i = 0; i < num_houses; i++) {
        ll x, y;
        cin >> x >> y;
        house_by_x[x].insert(y);
        house_by_y[y].insert(x);
    }
    
    int visited_houses = 0;
    
    // Process each movement
    for(int i = 0; i < num_movements; i++) {
        char direction;
        ll distance;
        cin >> direction >> distance;
        
        if (direction == 'U') {
            ll new_y = santa_y + distance;
            // Find houses on current x-coordinate between current and new y
            auto& houses_at_x = house_by_x[santa_x];
            auto it = houses_at_x.lower_bound(santa_y);
            
            // Process all houses in range
            while(it != houses_at_x.end() && *it <= new_y) {
                visited_houses++;
                house_by_y[*it].erase(santa_x);  // Remove from other map
                it = houses_at_x.erase(it);      // Remove and get next iterator
            }
            santa_y = new_y;
            
        } else if (direction == 'D') {
            ll new_y = santa_y - distance;
            auto& houses_at_x = house_by_x[santa_x];
            auto it = houses_at_x.lower_bound(new_y);
            
            while(it != houses_at_x.end() && *it <= santa_y) {
                visited_houses++;
                house_by_y[*it].erase(santa_x);
                it = houses_at_x.erase(it);
            }
            santa_y = new_y;
            
        } else if (direction == 'L') {
            ll new_x = santa_x - distance;
            auto& houses_at_y = house_by_y[santa_y];
            auto it = houses_at_y.lower_bound(new_x);
            
            while(it != houses_at_y.end() && *it <= santa_x) {
                visited_houses++;
                house_by_x[*it].erase(santa_y);
                it = houses_at_y.erase(it);
            }
            santa_x = new_x;
            
        } else { // direction == 'R'
            ll new_x = santa_x + distance;
            auto& houses_at_y = house_by_y[santa_y];
            auto it = houses_at_y.lower_bound(santa_x);
            
            while(it != houses_at_y.end() && *it <= new_x) {
                visited_houses++;
                house_by_x[*it].erase(santa_y);
                it = houses_at_y.erase(it);
            }
            santa_x = new_x;
        }
    }
    
    // Output final position and number of houses visited
    cout << santa_x << ' ' << santa_y << ' ' << visited_houses << endl;
    
    return 0;
}