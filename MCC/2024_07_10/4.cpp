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
    string a, b, c;
    cin >> a >> b >> c;
    int turn = 0;
    while (true) {
        switch (turn) {
        case 0:
            if (a.size() == 0) {
                cout << "A" << endl;
                return 0;
            }
            turn = a[0] - 'a';
            a = a.substr(1, a.size() - 1);
            break;
        case 1:
            if (b.size() == 0) {
                cout << "B" << endl;
                return 0;
            }
            turn = b[0] - 'a';
            b = b.substr(1, b.size() - 1);
            break;
        case 2:
            if (c.size() == 0) {
                cout << "C" << endl;
                return 0;
            }
            turn = c[0] - 'a';
            c = c.substr(1, c.size() - 1);
            break;
        default:
            break;
        }
    }
}
