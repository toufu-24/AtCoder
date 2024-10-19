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
    assert(n % 2 == 0);
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n / 2; i++) {
        int start = i;
        int end = n - i - 1;
        for (int j = start; j < end; j++) {
            for (int k = 0; k < (i + 1) % 4; k++) {
                char top = a[start][j];
                char right = a[j][end];
                char bottom = a[end][end - (j - start)];
                char left = a[end - (j - start)][start];

                a[start][j] = left;
                a[j][end] = top;
                a[end][end - (j - start)] = right;
                a[end - (j - start)][start] = bottom;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
}