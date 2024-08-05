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
    int N, A, B;
    cin >> N >> A >> B;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        string s = to_string(i);
        int sum = 0;
        for (int j = 0; j < s.size(); j++) {
            sum += s[j] - '0';
        }

        if (A <= sum && sum <= B) {
            ans += i;
        }
    }
    cout << ans << endl;
}
