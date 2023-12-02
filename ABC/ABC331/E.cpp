#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, M, L;
    cin >> N >> M >> L;
    vector<int> a(N), b(M);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    for (int j = 0; j < M; j++)
    {
        cin >> b[j];
    }

    vector<pair<int, int>> a_index(N), b_index(M);
    for (int i = 0; i < N; i++)
    {
        a_index[i] = {a[i], i};
    }
    for (int j = 0; j < M; j++)
    {
        b_index[j] = {b[j], j};
    }
    RSORT(a_index);
    RSORT(b_index);

    map<int, set<int>> mp;
    for (int i = 0; i < L; i++)
    {
        int c, d;
        cin >> c >> d;
        c--;
        d--;
        mp[c].insert(d);
    }

    int max_cost = 0;
    for (int i = 0; i < N; i++)
    {
        int cost = a_index[i].first;
        for (int j = 0; j < M; j++)
        {
            if (!mp[a_index[i].second].count(b_index[j].second))
            {
                cost += b_index[j].first;
                break;
            }
        }
        max_cost = max(max_cost, cost);
    }
    cout << max_cost << endl;
}