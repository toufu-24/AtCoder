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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<pair<int, int>> A_index;
    for (int i = 0; i < N; i++)
    {
        A_index.push_back({A[i], i});
    }
    SORT(A_index);
    vector<int> sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + A_index[i].first;
    }
    map<int, int> mp;
    for (int i = 0; i < N; i++)
    {
        if (mp.count(A_index[i].first))
            mp[A_index[i].first] = min(mp[A_index[i].first], sum[N] - sum[i + 1]);
        else
            mp[A_index[i].first] = sum[N] - sum[i + 1];
    }
    for (int i = 0; i < N; i++)
    {
        cout << mp[A[i]] << " ";
    }
}