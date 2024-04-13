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
    string S;
    cin >> S;
    vector<int> cnt(26, 0);
    for (int i = 0; i < S.size(); i++)
    {
        cnt[S[i] - 'a']++;
    }

    vector<int> cnt2(S.size() + 1, 0);
    for (int i = 0; i < 26; i++)
    {
        cnt2[cnt[i]]++;
    }

    for (int i = 1; i < cnt2.size(); i++)
    {
        if (cnt2[i] != 0 && cnt2[i] != 2)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
