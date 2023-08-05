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
    int N, X;
    cin >> N >> X;
    string ans;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ans += 'A' + i;
        }
    }
    cout << ans[X - 1];
}