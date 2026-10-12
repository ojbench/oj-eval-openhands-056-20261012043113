#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Interval {
    int l, r;
    bool operator<(const Interval& other) const {
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    set<Interval> activities;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            
            int deleted_count = 0;
            
            // Find all intervals that overlap with [l, r]
            auto it = activities.lower_bound({l, 0});
            
            // Check intervals that start before or at r
            vector<Interval> to_delete;
            
            // First, check intervals that might start before l but overlap
            auto it_prev = it;
            if (it_prev != activities.begin()) {
                --it_prev;
                if (it_prev->r >= l) {
                    to_delete.push_back(*it_prev);
                }
            }
            
            // Then check intervals that start at or after l
            while (it != activities.end() && it->l <= r) {
                to_delete.push_back(*it);
                ++it;
            }
            
            // Delete all overlapping intervals
            for (const auto& interval : to_delete) {
                activities.erase(interval);
                deleted_count++;
            }
            
            // Add the new mandatory class
            activities.insert({l, r});
            
            cout << deleted_count << "\n";
            
        } else if (op == 'B') {
            cout << activities.size() << "\n";
        }
    }
    
    return 0;
}