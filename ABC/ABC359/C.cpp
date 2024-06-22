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
    int Sx, Sy;
    cin >> Sx >> Sy;
    int Tx, Ty;
    cin >> Tx >> Ty;
    // ジグザグが一番いいはず？
    bool Sright = false;
    if ((Sx + Sy) % 2 != 0)
    {
        Sright = true;
    }
    // Sright == true なら左方向に寛容
    // Sright == false なら右方向に寛容
    if (Sright)
    {
        if (Tx < Sx)
        {
            Sx--;
        }
    }
    else
    {
        if (Tx > Sx)
        {
            Sx++;
        }
    }

    bool Tright = false;
    if ((Tx + Ty) % 2 != 0)
    {
        Tright = true;
    }
    // Tright == true なら左方向に寛容
    // Tright == false なら右方向に寛容
    if (Tright)
    {
        if (Sx < Tx)
        {
            Tx--;
        }
    }
    else
    {
        if (Sx > Tx)
        {
            Tx++;
        }
    }
    int diffx = abs(Tx - Sx);
    int diffy = abs(Ty - Sy);
    cerr << "diffx: " << diffx << endl;
    cerr << "diffy: " << diffy << endl;

    // 1回の上がる行為で1進める
    int end_Sx = Sx;
    if (Sx < Tx)
    {
        end_Sx += diffy;
        end_Sx = min(end_Sx, Tx);
    }
    else
    {
        end_Sx -= diffy;
        end_Sx = max(end_Sx, Tx);
    }
    int ans = diffy;
    int diff = abs(end_Sx - Tx);
    ans += (diff + 1) / 2;
    cout << ans << endl;
}
