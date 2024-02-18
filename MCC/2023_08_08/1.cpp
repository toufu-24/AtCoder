#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

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
    reverse(h);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        if (h[i] >= K)
        {
            ans++;
        }
        else
        {
            break;
        }
    }
    cout << ans << endl;
}