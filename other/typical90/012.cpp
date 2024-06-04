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
    vector<vector<bool>> masu(H, vector<bool>(W, false));
    int Q;
    cin >> Q;
    dsu d(H * W);
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    while (Q--)
    {
        int op;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            int r, c;
            cin >> r >> c;
            r--, c--;
            masu[r][c] = true;
            for (int i = 0; i < 4; i++)
            {
                int nx = r + dx[i];
                int ny = c + dy[i];
                if (0 <= nx && nx < H && 0 <= ny && ny < W && masu[nx][ny])
                {
                    d.merge(r * W + c, nx * W + ny);
                }
            }
            break;
        }
        case 2:
        {
            int ra, ca, rb, cb;
            cin >> ra >> ca >> rb >> cb;
            ra--, ca--, rb--, cb--;
            if (masu[ra][ca] && masu[rb][cb] && d.same(ra * W + ca, rb * W + cb))
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
            break;
        }
        }
    }
}
