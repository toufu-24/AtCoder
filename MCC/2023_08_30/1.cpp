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
    vector<int> c(N);
    for (int i = 0; i < N; i++)
    {
        cin >> c[i];
    }
    map<int, int> candy;
    for (int i = 0; i < K; i++)
    {
        candy[c[i]]++;
    }
    int ans = candy.size();
    for (int i = K; i < N; i++)
    {
        candy[c[i]]++;
        candy[c[i - K]]--;
        if (candy[c[i - K]] == 0)
        {
            candy.erase(c[i - K]);
        }
        ans = max(ans, (int)candy.size());
    }
    cout << ans;
}
