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
    ll D;
    cin >> D;
    vector<ll> pows;
    int i;
    for (i = 1; i * i <= D + 100; i++)
    {
        pows.push_back(i * i);
    }
    i++;
    if (i * i > 0)
        pows.push_back(i * i);
    i++;
    if (i * i > 0)
        pows.push_back(i * i);
    SORT(pows);
    assert(pows[0] == 1);
    int ans = numeric_limits<int>::max();
    for (int i = 0; i < pows.size(); i++)
    {
        int idx = lower_bound(all(pows), D - pows[i]) - pows.begin();
        int idx2 = idx - 1;
        int idx3 = upper_bound(all(pows), D - pows[i]) - pows.begin();
        if (idx >= 0 && idx < pows.size())
            ans = min(ans, abs(pows[i] + pows[idx] - D));
        if (idx2 >= 0)
            ans = min(ans, abs(pows[i] + pows[idx2] - D));
        if (idx3 < pows.size())
            ans = min(ans, abs(pows[i] + pows[idx3] - D));
    }
    cout << ans << endl;
}
