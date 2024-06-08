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
    string S;
    cin >> S;
    int low_cnt = 0, up_cnt = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (islower(S[i]))
            low_cnt++;
        else
            up_cnt++;
    }
    if (up_cnt > low_cnt)
        transform(all(S), S.begin(), ::toupper);
    else
        transform(all(S), S.begin(), ::tolower);
    cout << S << endl;
}
