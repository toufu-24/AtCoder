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
    ll N, M;
    cin >> N >> M;
    vector<ll> L(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> L[i];
    }
    ll left = *max_element(all(L));
    ll right = 1e18;

    while (right - left > 1)
    {
        ll mid = (left + right) / 2;
        ll lines = 1;
        ll line_width = L[0];

        for (ll i = 1; i < N; i++)
        {
            if (line_width + 1 + L[i] <= mid)
            {
                line_width += 1 + L[i];
            }
            else
            {
                lines++;
                line_width = L[i];
            }
        }

        if (lines > M)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    cout << right << endl;
}