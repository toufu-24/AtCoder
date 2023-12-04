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

int main()
{
    int M;
    cin >> M;
    vector<string> S(3);
    for (int i = 0; i < 3; i++)
    {
        cin >> S[i];
    }
    int ans = 1e9;
    for (int i = 0; i < 10; i++)
    {
        char c = '0' + i;
        vector<int> perm(3);
    }
    cout << (ans == 1e9 ? -1 : ans);
}