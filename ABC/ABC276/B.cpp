#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> road(M);
    for (int i = 0; i < M; i++)
    {
        cin >> road[i].first >> road[i].second;
    }
    vector<set<int>> ans(N + 1, set<int>());
    sort(road);
    for (int i = 0; i < M; i++)
    {
        ans[road[i].first].insert(road[i].second);
        ans[road[i].second].insert(road[i].first);
    }
    for (int i = 1; i <= N; i++)
    {
        cout << ans[i].size() << " ";
        for (auto value : ans[i])
        {
            cout << value << " ";
        }
        cout << endl;
    }
}
