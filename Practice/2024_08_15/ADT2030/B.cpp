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

vector<vector<string>> no = {
    {"#.",
     ".#"},
    {".#",
     "#."},
};
int32_t main() {
    vector<string> s(2);
    cin >> s[0] >> s[1];

    for (int i = 0; i < no.size(); i++) {
        if (s == no[i]) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
