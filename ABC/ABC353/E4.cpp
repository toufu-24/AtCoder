#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    SORT(S);

    map<string, int> prefix;
    for (int i = 0; i < N; i++)
    {
        string now = "";
        for (int j = 0; j < S[i].size(); j++)
        {
            now += S[i][j];
            prefix[now] = max(prefix[now], i);
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        vector<int> cnt(S[i].size() + 2, 0);
        string pre = "";
        for (int size = 1; size <= S[i].size(); size++)
        {
            pre += S[i][size - 1];
            int idx = prefix[pre];
            cnt[size] = max(0L, idx - i);
        }
        for (int size = 1; size <= S[i].size(); size++)
        {
            ans += (cnt[size] - cnt[size + 1]) * size;
        }
    }
    cout << ans << endl;
}
