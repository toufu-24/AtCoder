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
    int h;
    cin >> h;
    int now = 0;
    int i = 0;
    while (true) {
        if (h < now) {
            break;
        }
        now += pow(2, i);
        i++;
    }
    cout << i << endl;
}
