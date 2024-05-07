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
    int t;
    cin >> t;
    while (t--)
    {
        string S;
        cin >> S;
        if (S > "atcoder")
        {
            cout << 0 << endl;
            continue;
        }
        // at~~なら1
        // ab~~なら1
        // aaab~~なら3
        // aaaz~~なら2
        // aaat~~なら3
        int ans = -1;
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] > 'a')
            {
                ans = i - (S[i] > 't');
                break;
            }
        }
        cout << ans << endl;
    }
}
