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
    double start = clock();
    int n;
    cin >> n;
    while (clock() - start <= 1.9 * CLOCKS_PER_SEC) {
        if (n == 1) {
            cout << "Yes" << endl;
            return 0;
        }
        string s = to_string(n);
        int sum = 0;
        for (int i = 0; i < s.size(); i++) {
            sum += (s[i] - '0') * (s[i] - '0');
        }
        n = sum;
    }
    cout << "No" << endl;
}
