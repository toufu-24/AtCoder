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
    string S, T;
    cin >> S >> T;
    queue<char> q;
    for (int i = 0; i < S.size(); i++)
    {
        q.push(S[i]);
    }

    vector<int> ans;
    for (int i = 0; i < T.size(); i++)
    {
        if (q.front() == T[i])
        {
            ans.push_back(i);
            q.pop();
        }
    }

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] + 1 << endl;
    }
}
