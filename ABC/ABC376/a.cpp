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
    int n, c;
    cin >> n >> c;
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    int ans = 0;
    int prev = -1e9;
    for (int i = 0; i < n; i++) {
        if(t[i] - prev >= c){
            ans++;
            prev = t[i];
        }
    }
    cout << ans << endl;
    
}
