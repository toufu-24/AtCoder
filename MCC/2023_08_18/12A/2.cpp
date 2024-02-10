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
    ll N;
    cin >> N;
    vector<char> ans;
    while (N != 0)
    {
        if (N % 2 == 0)
        {
            ans.push_back('B');
            N /= 2;
        }
        else
        {
            ans.push_back('A');
            N--;
        }
    }
    reverse(ans);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
    }
}