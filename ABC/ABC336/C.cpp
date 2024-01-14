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
    if (N == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    N--;
    // 5進数に変換
    vector<int> v;
    while (N > 0)
    {
        v.push_back(N % 5);
        N /= 5;
    }

    vector<int> change = {0, 2, 4, 6, 8};
    vector<int> ans;
    for (int i = 0; i < v.size(); i++)
    {
        ans.push_back(change[v[i]]);
    }

    for (int i = ans.size() - 1; i >= 0; i--)
    {
        cout << ans[i];
    }
}