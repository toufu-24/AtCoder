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
    int n;
    cin >> n;
    vector<int> dist(n, 0);
    vector<int> d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> d[i];
        dist[i + 1] = dist[i] + d[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << dist[j] - dist[i] << " ";
        }
        cout << endl;
    }
}
