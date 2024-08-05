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
    vector<vector<int>> g(N);
    for (int i = 1; i < N; i++) {
        int a;
        cin >> a;
        a--;
        g[a].push_back(i);
    }

    for (int i = 0; i < N; i++) {
        cout << g[i].size() << endl;
    }
}
