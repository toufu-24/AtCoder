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
    int N;
    cin >> N;
    map<int, multiset<int>> mp;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<int> W(N);
    for (int i = 0; i < N; i++) {
        cin >> W[i];
    }

    for (int i = 0; i < N; i++) {
        mp[A[i]].insert(W[i]);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        while (mp[A[i]].size() > 1) {
            int x = *mp[A[i]].begin();
            mp[A[i]].erase(mp[A[i]].begin());
            ans += x;
        }
    }
    cout << ans << endl;
}
