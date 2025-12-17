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

// https://drken1215.hatenablog.com/entry/2023/05/20/200517#chap5 を改変
// G[v] := 頂点 v の行き先の頂点
vector<int> detect_cycle(const vector<int> &G, int st, int sz) {
    // 頂点を 1 つ好きに選んで、N 回移動する
    int v = st;
    for (int i = 0; i < sz; ++i)
        v = G[v];

    // 得られた頂点から出発してサイクルを検出する
    vector<int> res;
    int start = v;
    do {
        res.push_back(v);
        v = G[v];
    } while (v != start);
    return res;
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<int> revp(n);
    vector<int> nyuuji(n, 0);
    dsu d(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        revp[p[i]] = i;
        d.merge(i, p[i]);
        nyuuji[p[i]]++;
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) {
            continue;
        }
        int sz = d.size(i);
        auto cy = detect_cycle(p, i, sz);
        int cysize = cy.size();
        queue<int> q;
        for (auto x : cy) {
            ans[x] = cysize - 1;
            q.push(x);
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (ans[revp[v]] == -1) {
                q.push(revp[v]);
                ans[(revp[v])] = ans[v] + 1;
            }
        }
    }
    cout << reduce(all(ans)) / 2 << endl;
}
