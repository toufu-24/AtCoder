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
    string n;
    cin >> n;
    int a = n.back() - '0';
    switch (a) {
    case 2:
    case 4:
    case 5:
    case 7:
    case 9:
        cout << "hon" << endl;
        break;
    case 1:
    case 6:
    case 8:
    case 0:
        cout << "pon" << endl;
        break;
    default:
        cout << "bon" << endl;
        break;
    }
}
