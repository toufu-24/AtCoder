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
    int m;
    cin >> m;

    vector<int> san;
    while (m > 0) {
        san.push_back(m % 3);
        m /= 3;
    }
    vector<int> ans;
    for (int i = 0; i < san.size(); i++) {
        for (int j = 0; j < san[i]; j++)
            ans.push_back(i);
    }

    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
}
