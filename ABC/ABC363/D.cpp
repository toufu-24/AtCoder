// chatGPTで解いてすみませんでした

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

int powl(int x, int n) {
    int res = 1;
    for (int i = 0; i < n; i++) {
        res *= x;
    }
    return res;
}

int32_t main() {
    int N;
    cin >> N;
    N--;
    if (N < 10) {
        cout << N << endl;
        return 0;
    }
    int len = 1;
    int cnt = 9;
    while (N > cnt) {
        len++;
        if (len % 2 == 0) {
            cnt += 9 * powl(10, (len / 2) - 1);
        } else {
            cnt += 9 * powl(10, len / 2);
        }
    }

    cnt -= 9 * powl(10, (len / 2) - (len % 2 == 0));
    int offset = N - cnt - 1;

    if (len % 2 == 0) {
        int first_half = powl(10, (len / 2) - 1) + offset;
        string s = to_string(first_half);
        string rev = s;
        REVERSE(rev);
        cout << s + rev << endl;
    } else {
        int first_half = powl(10, len / 2) + offset;
        string s = to_string(first_half);
        string rev = s;
        REVERSE(rev);
        cout << s + rev.substr(1) << endl;
    }
}