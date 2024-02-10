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
    char c[N];
    for (int i = 0; i < N; i++)
    {
        cin >> c[i];
    }

    int ans = 0;
    int left = 0, right = N - 1;
    bool flag = true;
    while (right >= left)
    {
        int red_idx = left, white_idx = right;
        for (int i = left; i < N; i++)
        {
            if (c[i] == 'W')
            {
                red_idx = i;
                flag = false;
                break;
            }
        }
        if (flag)
            break;
        flag = true;
        for (int i = right; i >= 0; i--)
        {
            if (c[i] == 'R')
            {
                white_idx = i;
                flag = false;
                break;
            }
        }
        if (flag)
            break;
        if (red_idx < white_idx)
        {
            swap(c[red_idx], c[white_idx]);
            ans++;
        }
        left = red_idx + 1;
        right = white_idx - 1;
    }

    cout << ans;
}