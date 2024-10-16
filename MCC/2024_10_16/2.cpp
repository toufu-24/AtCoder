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
    bool strong = true;
    string s_x = x, r_x = x;
    SORT(s_x);
    RSORT(r_x);
    if (s_x == r_x) strong = false;
    bool weak = true;
    for (int i = 0; i < 3; i++) {
        if ((x[i] - '0' + 1) % 10 != x[i + 1] - '0')
            weak = false;
    }
    if (!strong || weak)
        cout << "Weak" << endl;
    else
        cout << "Strong" << endl;
}
