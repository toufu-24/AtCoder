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
    vector<int> point(5);
    for (int i = 0; i < 5; i++) {
        cin >> point[i];
    }
    vector<pair<int, vector<int>>> ans;
    for (int i = 1; i < (1 << 5); i++) {
        vector<int> tmp;
        int sum = 0;
        for (int j = 0; j < 5; j++) {
            if (i & (1 << j)) {
                tmp.push_back(j);
                sum += point[j];
            }
        }
        ans.push_back({sum, tmp});
    }
    sort(all(ans), [](pair<int, vector<int>> a, pair<int, vector<int>> b) {
        if (a.first != b.first) {
            return a.first > b.first;
        } else {
            string aa, bb;
            for (int i = 0; i < a.second.size(); i++) {
                aa += char(a.second[i] + 'A');
            }
            for (int i = 0; i < b.second.size(); i++) {
                bb += char(b.second[i] + 'A');
            }
            return aa < bb;
        }
    });
    assert(ans.size() == 31);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].second.size(); j++) {
            cout << char(ans[i].second[j] + 'A');
        }
        cout << endl;
    }
}
