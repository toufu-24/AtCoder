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
    string x;
    cin >> x;
    while (x.back() == '0') {
        x.pop_back();
    }
    if(x.back() == '.') {
        x.pop_back();
    }
    cout << x << endl;
}
