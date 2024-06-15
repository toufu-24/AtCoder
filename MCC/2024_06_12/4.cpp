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
    int N;
    cin >> N;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<int, int> mp;
    vector<int> S(N), C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i] >> C[i];
    }

    for (int i = 0; i < N; i++)
    {
        pq.push({S[i], C[i]});
        mp[S[i]] = C[i];
    }

    int ans = 0;
    while (!mp.empty())
    {
        auto [s, c] = *mp.begin();
        if (c / 2 != 0)
        {
            mp[s * 2] += c / 2;
        }
        mp.erase(s);
        ans += c % 2;
    }

    cout << ans << endl;
}
