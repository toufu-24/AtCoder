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
    int H, W;
    cin >> H >> W;
    vector<string> a(H);
    for (int i = 0; i < H; i++)
    {
        cin >> a[i];
    }

    while (true)
    {
        bool flag = false;
        // 列を見る
        for (int i = 0; i < H; i++)
        {
            if (count(all(a[i]), '.') == W)
            {
                a.erase(a.begin() + i);
                H--;
                flag = true;
                break;
            }
        }
        // 行を見る
        for (int i = 0; i < W; i++)
        {
            bool f = true;
            for (int j = 0; j < H; j++)
            {
                if (a[j][i] != '.')
                {
                    f = false;
                    break;
                }
            }
            if (f)
            {
                W--;
                for (int j = 0; j < H; j++)
                {
                    a[j].erase(a[j].begin() + i);
                }
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            break;
        }
    }
    for (int i = 0; i < H; i++)
    {
        cout << a[i] << endl;
    }
}
