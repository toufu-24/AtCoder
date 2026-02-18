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
    int n, x;
    cin >> n >> x;
    vector<int> v(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> p[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i] * p[i];
        if(sum > x * 100){
            cout << i + 1 << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
