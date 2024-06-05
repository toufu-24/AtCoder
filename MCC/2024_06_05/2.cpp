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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A[i]--;
    }
    map<int, int> mp;
    for (int i = 0; i < N; i++)
    {
        mp[A[i]] = i;
    }

    int st;
    for (int i = 0; i < N; i++)
    {
        if (A[i] == -2)
        {
            st = i;
            break;
        }
    }

    vector<int> ans;
    ans.push_back(st);
    for (int i = 1; i < N; i++)
    {
        ans.push_back(mp[ans.back()]);
    }

    for (int i = 0; i < N; i++)
    {
        cout << ans[i] + 1 << " ";
    }
}
