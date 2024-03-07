#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    string ans = "";
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'o' && cnt < K)
        {
            ans += 'o';
            cnt++;
        }
        else
        {
            ans += 'x';
        }
    }
    cout << ans;
}