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

struct Compare
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        if (a.first == b.first)
        {
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};

int main()
{
    ll N, M;
    cin >> N >> M;
    vector<ll> T(M), W(M), S(M);
    for (int i = 0; i < M; i++)
    {
        cin >> T[i] >> W[i] >> S[i];
    }
    vector<ll> somen(N, 0);
    vector<ll> back(N, -1);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    for (int i = 0; i < N; i++)
    {
        pq.push(make_pair(0, i));
    }

    for (int i = 0; i < M; i++)
    {
        int eater = -1;
        if (pq.top().first > T[i])
        {
            continue;
        }
        eater = pq.top().second;
        pq.pop();
        somen[eater] += W[i];
        back[eater] = T[i] + S[i];
        pq.push(make_pair(back[eater], eater));
    }

    for (int i = 0; i < N; i++)
    {
        cout << somen[i] << '\n';
    }
}