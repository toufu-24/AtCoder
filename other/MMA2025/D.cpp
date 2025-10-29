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
    int n, m, t;
    cin >> n >> m >> t;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> times(n, 0);
    for (int i = 0; i < m; i++) {
        times[a[i]]++;
    }
    SORT(times);
    multiset<int> times_set;
    for (int i = 0; i < n; i++) {
        times_set.insert(times[i]);
    }
    while (true) {
        int min_time = *times_set.begin();
        int max_time = *times_set.rbegin();

        int new_min_time = min_time + t;
        int new_max_time = max_time - 1;

        if (new_min_time >= max_time) {
            break;
        }
        times_set.erase(times_set.find(min_time));
        times_set.erase(times_set.find(max_time));
        times_set.insert(new_min_time);
        times_set.insert(new_max_time);
    }
    cout << *times_set.rbegin() << endl;
}