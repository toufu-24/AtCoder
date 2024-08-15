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

int arr[] = {1, 4, 27, 256, 3125, 46656, 823543, 16777216, 387420489, 10000000000, 285311670611, 8916100448256, 302875106592253, 11112006825558016, 437893890380859375};
int32_t main() {
    int b;
    cin >> b;
    for (int i = 0; i < 15; i++) {
        if (arr[i] == b) {
            cout << i + 1 << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
