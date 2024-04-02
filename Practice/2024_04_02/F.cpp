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
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    map<string, int> mp;
    for (int i = 0; i < N; i++)
    {
        cout << S[i];
        if (mp.contains(S[i]))
        {
            mp[S[i]]++;
            cout << '(' << mp[S[i]] << ')' << endl;
        }
        else
        {
            mp[S[i]] = 0;
        }
        cout << endl;
    }
}
