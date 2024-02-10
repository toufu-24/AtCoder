#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, K, L;
    cin >> N >> K >> L;
    vector<vector<int>> roadG(N);
    dsu road(N);
    for (int i = 0; i < K; i++)
    {
        int p, q;
        cin >> p >> q;
        roadG[p - 1].push_back(q - 1);
        roadG[q - 1].push_back(p - 1);
        road.merge(p - 1, q - 1);
    }
    vector<vector<int>> railG(N);
    dsu rail(N);
    for (int i = 0; i < L; i++)
    {
        int r, s;
        cin >> r >> s;
        railG[r - 1].push_back(s - 1);
        railG[s - 1].push_back(r - 1);
        rail.merge(r - 1, s - 1);
    }
    vector<int> ans(N, 0);
    // leaderのペアをキーとして、そのペアの出現回数が値
    map<pair<int, int>, int> mp;
    for (int i = 0; i < N; i++)
    {
        mp[{road.leader(i), rail.leader(i)}]++;
    }
    for (int i = 0; i < N; i++)
    {
        cout << mp[{road.leader(i), rail.leader(i)}] << " ";
    }
}