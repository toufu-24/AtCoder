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
    vector<pair<int, int>> jumped(n);
    vector<int> x(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> r[i];
        jumped[i] = {x[i] + r[i], x[i] - r[i]};
    }
    map<int, set<int>> kouho;
    for (int i = 0; i < n; i++) {
        kouho[x[i] + r[i]].insert(i);
        kouho[x[i] - r[i]].insert(i);
    }
    // aをキーとする，bのサイズ順にでてくる
    set<tuple<int, int>> size_arrive;
    map<int, int> arrive_size;
    for (auto [a, b] : kouho) {
        size_arrive.insert({b.size(), a});
        arrive_size[a] = b.size();
    }

    set<int> already;
    while (!size_arrive.empty()) {
        auto [size, arrival] = *size_arrive.begin();
        size_arrive.erase(size_arrive.begin());
        arrive_size.erase(arrival);

        if (already.contains(arrival)) {
            continue;
        }
        already.insert(arrival);

        // 後処理
        auto ko = kouho[arrival];
        // beginを使ったものとする
        auto used = *ko.begin();

        int inv = (x[used] + r[used] == arrival) ? x[used] - r[used] : x[used] + r[used];
        size_arrive.erase({kouho[inv].size(), inv});

        kouho[x[used] + r[used]].erase(used);
        kouho[x[used] - r[used]].erase(used);
        if (kouho[inv].size() != 0) {
            size_arrive.insert({kouho[inv].size(), inv});
            arrive_size[inv]--;
        } else {
            arrive_size.erase(inv);
            kouho.erase(inv);
        }
    }
    cout << already.size() << endl;
}
