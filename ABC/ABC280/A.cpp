#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int H, W;
    cin >> H >> W;
    int cnt = 0;
    for (int i = 0; i < H; i++)
    {
        string S;
        cin >> S;
        for (int j = 0; j < W; j++)
        {
            if (S[j] == '#')
                cnt++;
        }
    }
    cout << cnt << endl;
}