#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    string S, T;
    cin >> S >> T;
    int ans = T[0] - S[0];
    if (ans < 0)
        ans += 26;
    else if (ans >= 26)
        ans -= 26;

    for (int i = 0; i < S.size(); i++)
    {
        int tmp = T[i] - S[i];
        if (tmp < 0)
            tmp += 26;
        else if (tmp >= 26)
            tmp -= 26;
        if (tmp != ans)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}