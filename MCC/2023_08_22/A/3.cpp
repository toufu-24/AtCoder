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
    int N, K;
    cin >> N >> K;
    vector<int> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i];
    }
    sort(h);
    queue<int> now;
    for (int i = 0; i < K - 1; i++)
    {
        now.push(h[i]);
    }
    int ans = 1e9;
    int now_minimum = h[0];

    for (int i = K - 1; i < N; i++)
    {
        now.push(h[i]);
        ans = min(ans, now.back() - now.front());
        now.pop();
    }
    cout << ans;
}