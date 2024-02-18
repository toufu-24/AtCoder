#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    string S;
    cin >> S;
    ll cnt = 0;
    int i;
    for (i = 0; i < S.size() - 1; i++)
    {
        if (S[i] == '0' && S[i + 1] == '0')
        {
            cnt++;
            i++;
        }
        else
        {
            cnt++;
        }
    }
    cnt += S.size() - i;
    cout << cnt;
}