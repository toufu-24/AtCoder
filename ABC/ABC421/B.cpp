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

int x, y;
int f(int n) {
    if (n == 1) {
        return x;
    }
    if (n == 2) {
        return y;
    }
    int tmp = f(n - 1) + f(n - 2);
    string str = to_string(tmp);
    REVERSE(str);
    return stoll(str);
}

int32_t main() {
    cin >> x >> y;
    cout << f(10) << endl;
}
