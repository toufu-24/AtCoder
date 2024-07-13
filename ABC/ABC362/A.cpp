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
    vector<int> c(3);
    for (int i = 0; i < 3; i++)
        cin >> c[i];
    string S;
    cin >> S;
    map<string, int> mp;
    mp["Red"] = 0;
    mp["Green"] = 1;
    mp["Blue"] = 2;
    int ng = mp[S];
    vector<int> v;
    for (int i = 0; i < 3; i++) {
        if (i == ng) continue;
        v.push_back(c[i]);
    }
    SORT(v);
    cout << v[0] << endl;
}
