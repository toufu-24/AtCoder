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
vector<bool> visited;
vector<pair<ll, ll>> place;
vector<vector<pair<ll, pair<ll, ll>>>> G;
ll N, M;

void dfs(ll prev)
{
    for (auto next : G[prev])
    {
        if (visited[next.first])
            continue;
        visited[next.first] = true;
        place[next.first].first = place[prev].first + next.second.first;
        place[next.first].second = place[prev].second + next.second.second;
        dfs(next.first);
    }
}

int main()
{
    cin >> N >> M;
    visited.resize(N, false);
    place.resize(N);
    G.resize(N);
    for (ll i = 0; i < M; i++)
    {
        ll A, B, X, Y;
        cin >> A >> B >> X >> Y;
        A--;
        B--;
        G[A].push_back(make_pair(B, make_pair(X, Y)));
        G[B].push_back(make_pair(A, make_pair(-X, -Y)));
    }
    visited[0] = true;
    place[0] = make_pair(0, 0);
    dfs(0);
    for (ll i = 0; i < N; i++)
    {
        if (visited[i])
        {
            cout << place[i].first << " " << place[i].second << endl;
        }
        else
        {
            cout << "undecidable" << endl;
        }
    }
}