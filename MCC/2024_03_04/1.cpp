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

int main()
{
    int N;
    cin >> N;
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        string s = to_string(i);
        if (s.size() % 2 == 1)
        {
            ans++;
        }
    }
    cout << ans;
}