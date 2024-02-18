#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N;
    cin >> N;
    vector<vector<int>> indexes(N);
    vector<int> same_idx;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        a[i]--;
        indexes[a[i]].push_back(i);
        if (a[i] == i)
        {
            same_idx.push_back(i);
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        // a[i] != iならa[j]がiになるようにする
        if (a[i] != i)
        {
            for (auto j : indexes[i])
            {
                assert(a[j] == i);
                if (a[i] == j && i < j)
                {
                    ans++;
                }
            }
        }
        // a[i] == iならa[j]がjになるようにする
        else
        {
            int idx = upper_bound(all(same_idx), i) - same_idx.begin();
            ans += same_idx.size() - idx;
        }
    }
    cout << ans << endl;
}