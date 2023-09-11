#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> box(N);
    for (int i = 0; i < N; i++)
    {
        cin >> box[i].first >> box[i].second;
    }
    sort(all(box),
         [](pair<int, int> a, pair<int, int> b)
         {
             if (a.first == b.first)
             {
                 return a.second > b.second;
             }
             else
             {
                 return a.first < b.first;
             }
         });

    vector<int> dp(N, 1e9);

    for (int i = 0; i < N; i++)
    {
        int idx = lower_bound(all(dp), box[i].second) - dp.begin();
        dp[idx] = box[i].second;
    }
    cout << lower_bound(all(dp), 1e9) - dp.begin() << endl;
}