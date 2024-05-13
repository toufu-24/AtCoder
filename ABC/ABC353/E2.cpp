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
    vector<vector<string>> prefix(N);
    for (int i = 0; i < N; i++)
    {
        string now = "";
        for (int j = 0; j < S[i].size(); j++)
        {
            now += S[i][j];
            prefix[i].push_back(now);
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        map<int, int> cnt;
        for (int size = 1; size <= S[i].size(); size++)
        {
            // size文字だけprefixが一致するものが何個あるかを二分探索
            int l = i, r = N;
            while (r - l > 1)
            {
                int mid = (l + r) / 2;
                if (S[mid].substr(0, size) == S[i].substr(0, size))
                {
                    l = mid;
                }
                else
                {
                    r = mid;
                }
            }
            cnt[size] = l - i;
        }
        for (int size = 1; size <= S[i].size(); size++)
        {
            ans += (cnt[size] - cnt[size + 1]) * size;
        }
    }
    cout << ans << endl;
}
