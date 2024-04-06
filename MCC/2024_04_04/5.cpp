#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

template <typename T, typename... Args>
auto vec(T x, int arg, Args... args)
{
    if constexpr (sizeof...(args) == 0)
        return vector<T>(arg, x);
    else
        return vector(arg, vec<T>(x, args...));
}

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    int N = S.size();
    map<int, char> mp;
    for (int i = 0; i < S.size() - 1; i++)
    {
        if (S[i] == S[i + 1])
        {
            mp[i + 2] = S[i];
        }
    }

    auto dp = vec(0LL, N + 1, 26);

    vector<vector<int>> cnt(26, vector<int>(N + 1, 0));
    for (int i = 0; i < 26; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cnt[i][j] = cnt[i][j - 1] + (S[j - 1] == 'a' + i);
        }
    }

    int ans = 0;
    set<int> st;
    for (auto [idx, c] : mp)
    {
        ans += N - idx + 1 - cnt[c - 'a'][N] + cnt[c - 'a'][idx - 1];
    }
    cout << ans << endl;
}
