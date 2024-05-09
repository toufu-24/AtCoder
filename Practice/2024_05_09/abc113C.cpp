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

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<int> P(M), Y(M);
    for (int i = 0; i < M; i++)
    {
        cin >> P[i] >> Y[i];
    }
    map<int, vector<pair<int, int>>> mp;
    for (int i = 0; i < M; i++)
    {
        mp[P[i]].push_back({Y[i], i});
    }
    for (auto &[v, idx] : mp)
    {
        SORT(idx);
    }
    vector<pair<int, string>> ans;
    ans.reserve(M);
    for (auto &[v, idx] : mp)
    {
        string p = to_string(v);
        while (p.size() < 6)
        {
            p = "0" + p;
        }
        int cnt = 1;
        for (int i = 0; i < idx.size(); i++)
        {
            string id = to_string(cnt++);
            while (id.size() < 6)
            {
                id = "0" + id;
            }
            ans.push_back({idx[i].second, p + id});
        }
    }
    SORT(ans);
    for (int i = 0; i < M; i++)
    {
        cout << ans[i].second << endl;
    }
}
