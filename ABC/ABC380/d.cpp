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
    string s;
    cin >> s;
    int n = s.size();
    int q;
    cin >> q;
    vector<int> k(q);
    for (int i = 0; i < q; i++) {
        cin >> k[i];
        k[i]--;
    }

    for (int i = 0; i < q; i++) {
        int out_idx = k[i] % n;
        int tmp = k[i] / n;
        int one_cnt = 0;
        vector<int> two;
        while (tmp > 0) {
            two.push_back(tmp % 2);
            tmp /= 2;
        }
        bool rev = false;
        for (int j = 0; j < two.size(); j++) {
            if (two[j] == 1) {
                rev = !rev;
            }
        }
        char c = s[out_idx];
        if (rev) {
            if (isupper(c)) {
                c = tolower(c);
            } else {
                c = toupper(c);
            }
        }
        cout << c << " ";
    }
}
