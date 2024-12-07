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

vector<long long> divisor(long long n) {
    vector<long long> ret;
    for (long long i = 1; i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(n / i);
        }
    }
    return ret;
}

int32_t main() {
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        auto divs = divisor(i);
        if (divs.size() == 9) {
            cout << i << endl;
        }
    }
}
