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

int ans = 0;
vector<int> num = {3, 5, 7};
void dfs(string s, int N, int mask)
{
    for (int i = 0; i < 3; i++)
    {
        string tmp = s + to_string(num[i]);
        int mask_next = mask;
        mask_next |= 1 << i;
        if (mask_next == 7)
        {
            if (stoll(tmp) <= N)
            {
                ans++;
            }
        }
        if (stoll(tmp) <= N)
            dfs(tmp, N, mask_next);
    }
}

int32_t main()
{
    int N;
    cin >> N;
    dfs("", N, 0);
    cout << ans << endl;
}
