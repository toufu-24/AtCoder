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
    string S, T;
    cin >> S >> T;
    for (int i = 0; i < N; i++) {
        if (S[i] == T[i]) {
        } else if (S[i] == '1' && T[i] == 'l') {
        } else if (S[i] == 'l' && T[i] == '1') {
        } else if (S[i] == '0' && T[i] == 'o') {
        } else if (S[i] == 'o' && T[i] == '0') {
        } else {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
