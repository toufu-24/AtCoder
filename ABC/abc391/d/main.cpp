#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main() {
    int n, w;
    cin >> n >> w;
    vector<pair<int, int>> xy(n);
    vector<bool> first_full(w, false);
    for (int i = 0; i < n; i++) {
        cin >> xy[i].first >> xy[i].second;
        xy[i].first--;
        xy[i].second--;
        if (xy[i].second == 0) {
            first_full[xy[i].first] = true;
        }
    }
    bool is_full = true;
    for (int i = 0; i < w; i++) {
        if (!first_full[i]) {
            is_full = false;
        }
    }
    vector<set<pair<int, int>>> where(w);
    for (int i = 0; i < n; i++) {
        where[xy[i].first].insert({xy[i].second, i});
    }
    vector<int> erase_time(n, 1e18);
    int last_time = 0;
    for (int i = 0; i < w; i++) {
        auto it = where[i].begin();
        int time = 0;
        int prev = 0;
        while (it != where[i].end()) {
            erase_time[it->second] = max(erase_time[it->second], time + diff);
            last_time = max(last_time, time);
            time = 
                it++;
        }
    }

    for (int i = 0; i < n; i++) {
        cerr << erase_time[i] << " ";
    }
    cerr << endl;
    cerr << last_time << endl;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, a;
        cin >> t >> a;
        t--;
        a--;

        if (t < erase_time[a]) {
            cout << "Yes" << endl;
        } else {
            if (last_time <= erase_time[a]) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}
