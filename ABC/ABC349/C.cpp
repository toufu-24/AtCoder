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
    string S, T;
    cin >> S >> T;
    int next_idx = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] - 'a' + 'A' == T[next_idx])
        {
            next_idx++;
        }
        if (next_idx == T.size())
        {
            break;
        }
    }
    if (next_idx == T.size())
    {
        cout << "Yes" << endl;
    }
    else
    {
        if (next_idx == T.size() - 1 && T[T.size() - 1] == 'X')
        {
            cout << "Yes" << endl;
            return 0;
        }
        cout << "No" << endl;
    }
}
