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
    int N;
    cin >> N;
    vector<int> p(N);
    for (int i = 0; i < N; i++)
    {
        cin >> p[i];
        p[i]--;
    }
    vector<int> need_swap;
    for (int i = 0; i < N; i++)
    {
        if (i == p[i])
        {
            need_swap.push_back(i);
        }
    }
    int ans = need_swap.size();
    if (ans == 0)
    {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < need_swap.size() - 1; i++)
    {
        if (need_swap[i] + 1 == need_swap[i + 1])
        {
            ans--;
            i++;
        }
    }
    cout << ans;
}