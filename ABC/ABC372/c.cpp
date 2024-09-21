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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    int cnt = 0;
    vector<bool> ABC_idx(n, false);
    for (int i = 0; i < n - 2; i++) {
        if (s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C') {
            cnt++;
            ABC_idx[i] = true;
            ABC_idx[i + 1] = true;
            ABC_idx[i + 2] = true;
            i += 2;
        }
    }
    while (q--) {
        int x;
        char c;
        cin >> x >> c;
        x--;
        if (s[x] == c) {
            cout << cnt << endl;
            continue;
        }
        if (ABC_idx[x]) {
            cnt--;
            switch (s[x]) {
                {
                case 'A':
                    ABC_idx[x] = false;
                    ABC_idx[x + 1] = false;
                    ABC_idx[x + 2] = false;
                    break;
                }
                {
                case 'B':
                    ABC_idx[x - 1] = false;
                    ABC_idx[x] = false;
                    ABC_idx[x + 1] = false;
                    break;
                }
                {
                case 'C':
                    ABC_idx[x - 2] = false;
                    ABC_idx[x - 1] = false;
                    ABC_idx[x] = false;
                    break;
                }
            }
        }
        switch (c) {
            {
            case 'A':
                if (x + 1 < n && s[x + 1] == 'B' && x + 2 < n && s[x + 2] == 'C') {
                    cnt++;
                    ABC_idx[x] = true;
                    ABC_idx[x + 1] = true;
                    ABC_idx[x + 2] = true;
                }
                break;
            }
            {
            case 'B':
                if (x - 1 >= 0 && s[x - 1] == 'A' && x + 1 < n && s[x + 1] == 'C') {
                    cnt++;
                    ABC_idx[x - 1] = true;
                    ABC_idx[x] = true;
                    ABC_idx[x + 1] = true;
                }
                break;
            }
            {
            case 'C':
                if (x - 2 >= 0 && s[x - 2] == 'A' && x - 1 >= 0 && s[x - 1] == 'B') {
                    cnt++;
                    ABC_idx[x - 2] = true;
                    ABC_idx[x - 1] = true;
                    ABC_idx[x] = true;
                }
                break;
            }
        }
        cout << cnt << endl;
        s[x] = c;
    }
}
