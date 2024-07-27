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
    int H, W;
    cin >> H >> W;
    pair<int, int> s;
    cin >> s.first >> s.second;
    s.first--;
    s.second--;
    vector<string> C(H);
    for (int i = 0; i < H; i++) {
        cin >> C[i];
    }
    string X;
    cin >> X;
    map<char, pair<int, int>> dir = {
        {'U', {-1, 0}},
        {'D', {1, 0}},
        {'L', {0, -1}},
        {'R', {0, 1}}};

    for (int x = 0; x < X.size(); x++) {
        pair<int, int> next = {s.first + dir[X[x]].first, s.second + dir[X[x]].second};
        if (next.first < 0 || next.first >= H || next.second < 0 || next.second >= W || C[next.first][next.second] == '#') {
            continue;
        }
        s = next;
    }

    cout << s.first + 1 << " " << s.second + 1 << endl;
}
