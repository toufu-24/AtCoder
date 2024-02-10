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
    vector<vector<ll>> kouho(2 * K, vector<ll>(K));
    for (int i = -K; i < K; i++)
    {
        int left = plus_first - 1;
        int right = plus_first;
        int cnt = 0;
        while (cnt < K)
        {
            if (left < 0)
            {
                kouho[i + K][cnt] = x[right];
                right++;
            }
            else if (right >= N || abs(x[left]) < x[right])
            {
                kouho[i + K][cnt] = x[left];
                left--;
            }
            else
            {
                kouho[i + K][cnt] = x[right];
                right++;
            }
            cnt++;
        }
    }
    for (int i = 0; i < 2 * K; i++)
    {
        sort(kouho[i]);
    }

    ll ans = 1e18;
    for (int i = 0; i < 2 * K; i++)
    {
        if (kouho[i][K - 1] < 0)
        {
            ans = min(ans, abs(kouho[i][0]));
        }
        else if (kouho[i][0] >= 0)
        {
            ans = min(ans, kouho[i][K - 1]);
        }
        else
        {
            ans = min(ans, abs(kouho[i][0]) + kouho[i][K - 1] + min(abs(kouho[i][0]), kouho[i].back()));
        }
    }
    cout << ans << endl;
}