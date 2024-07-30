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
    string S;
    cin >> S;
    SORT(S);
    if (S[0] != S[1] && S[0] != S[2]) {
        cout << S[0] << endl;
    } else if (S[1] != S[0] && S[1] != S[2]) {
        cout << S[1] << endl;
    } else if (S[2] != S[0] && S[2] != S[1]) {
        cout << S[2] << endl;
    } else {
        cout << -1 << endl;
    }
}
