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
    int D, N;
    cin >> D >> N;
    int ans_cnt = 0;
    for (int i = 1; i <= 10000000; i++) {
        int cnt = 0;
        int tmp = i;
        while (tmp % 100 == 0) {
            tmp /= 100;
            cnt++;
        }
        if (cnt == D) {
            ans_cnt++;
            if (ans_cnt == N) {
                cout << i << endl;
                return 0;
            }
        }
    }
}
