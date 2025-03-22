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
    int cnt = n / 2 - (n % 2 == 0);
    for (int i = 0; i < cnt; i++) {
        cout << '-';
    }
    cout << '=';
    if (n % 2 == 0) {
        cout << '=';
    }
    for (int i = 0; i < cnt; i++) {
        cout << '-';
    }
    cout << endl;
}
