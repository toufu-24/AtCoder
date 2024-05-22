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
    vector<pair<string, int>> SC(N);
    for (int i = 0; i < N; i++)
    {
        cin >> SC[i].first >> SC[i].second;
    }
    SORT(SC);
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += SC[i].second;
    }
    cout << SC[sum % N].first << endl;
}