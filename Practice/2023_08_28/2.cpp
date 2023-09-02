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
    string S;
    cin >> S;
    int ans = 0;
    for (int i = 1; i < S.size() - 1; i += 2)
    {
        string left = S.substr(0, i / 2);
        string right = S.substr(i / 2 + 1, i / 2);
        if (left == right)
        {
            ans = i + 1;
        }
    }
    cout << ans << endl;
}