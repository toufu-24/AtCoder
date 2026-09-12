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
    int n, s, l;
    cin >> n >> s >> l;
    vector<int> a(n + 2);
    a[0] = 1e15;
    a[n + 1] = 1e15;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 右で折り返す
    int left_ans = 1;
    int left_dis = 0;
    int prev_dis = 0;
    int left = s - 1, right = s + 1;
    while (left_dis < l) {
        if (a[left] < a[right - 1] * 2) {
            left_dis += a[left];
            left_ans++;
        } else {
            left_dis += a[right - 1] * 2;
            left_ans++;
        }
    }
}
