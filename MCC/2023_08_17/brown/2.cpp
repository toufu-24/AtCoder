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
    cout << fixed << setprecision(10);
    int N;
    cin >> N;
    vector<pair<ld, ld>> fuse(N);
    ld length = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> fuse[i].first >> fuse[i].second;
        length += fuse[i].first;
    }
    if (N == 1)
    {
        cout << length / 2 << endl;
        return 0;
    }
    vector<ld> seconds(N);
    for (int i = 0; i < N; i++)
    {
        seconds[i] = fuse[i].first / fuse[i].second;
    }
    vector<ld> sum(N);
    sum[0] = seconds[0];
    for (int i = 1; i < N; i++)
    {
        sum[i] = sum[i - 1] + seconds[i];
    }
    ld ans_sec = sum[N - 1] / 2;
    ld ans_length = 0;
    for (int i = 0; i < N; i++)
    {
        if (ans_sec <= sum[i])
        {
            ans_length += (ans_sec - sum[i - 1]) * fuse[i].second;
            break;
        }
        else
        {
            ans_length += fuse[i].first;
        }
    }
    cout << ans_length << endl;
}