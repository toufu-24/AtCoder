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

int main()
{
    int N;
    cin >> N;
    vector<ll> rep(12);
    string s = "";
    for (int i = 0; i < 12; i++)
    {
        s += "1";
        rep[i] = stoll(s);
    }

    set<ll> ans;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            for (int k = 0; k < 12; k++)
            {
                if (rep[i] + rep[j] + rep[k] >= 0)
                    ans.insert(rep[i] + rep[j] + rep[k]);
            }
        }
    }
    int cnt = 0;
    cerr << ans.size() << endl;
    for (auto x : ans)
    {
        cnt++;
        if (cnt == N)
            cout << x << endl;
    }
}