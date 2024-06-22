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
    int N;
    cin >> N;
    int cnt = 0;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        if (S[i] == "Takahashi")
        {
            cnt++;
        }
    }
    cout << cnt;
}
