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
    ll N, K;
    cin >> N >> K;
    vector<int> x(N);
    for (int i = 0; i < N; i++)
    {
        cin >> x[i];
    }
    int plus_first = lower_bound(all(x), 0) - x.begin();
    vector<int> ans;
    int left = plus_first - 1;
    int right = plus_first;
    while (ans.size() < K)
    {
        if (left < 0)
        {
            ans.push_back(x[right]);
            right++;
        }
        else if (right >= N || abs(x[left]) < x[right])
        {
            ans.push_back(x[left]);
            left--;
        }
        else
        {
            ans.push_back(x[right]);
            right++;
        }
    }
    sort(ans);
    if (ans[0] < 0 && ans[K - 1] < 0)
        cout << abs(ans[0]) << endl;
    else if (ans[0] >= 0 && ans[K - 1] >= 0)
        cout << ans[K - 1] << endl;
    else
        cout << abs(ans[0]) + abs(ans[K - 1]) + min(abs(ans[0]), abs(ans[K - 1])) << endl;
}