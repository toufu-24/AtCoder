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
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto ori_a = a;
    for (int i = 0; i < n / 2; i++) {
        // i段目をj回回す
        for (int j = 0; j < (i + 1) % 4; j++) {
            for (int k = i; k < n - i - 1; k++) {
                pair<int, int> top = {i, k};
                pair<int, int> right = {k, n - i - 1};
                pair<int, int> bottom = {n - i - 1, n - k - 1};
                pair<int, int> left = {n - k - 1, i};
                char top_c = a[top.first][top.second];
                char right_c = a[right.first][right.second];
                char bottom_c = a[bottom.first][bottom.second];
                char left_c = a[left.first][left.second];
                a[right.first][right.second] = top_c;
                a[bottom.first][bottom.second] = right_c;
                a[left.first][left.second] = bottom_c;
                a[top.first][top.second] = left_c;
            }
        }
    }
    for (const auto &x : a) {
        cout << x << endl;
    }
}
