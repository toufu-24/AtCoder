#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

map<tuple<int, int, int>, vector<tuple<int, int, int>>> g;

// 頂点をswapする
void vertex_swap(tuple<int, int, int> v1, tuple<int, int, int> v2)
{
    tuple<int, int, int> tmp1 = v1;
    tuple<int, int, int> tmp2 = v2;
    swap(get<2>(tmp1), get<2>(tmp2));
    for (auto &i : g[v1])
    {
        if (i == v2)
        {
            i = tmp2;
        }
    }
    for (auto &i : g[v2])
    {
        if (i == v1)
        {
            i = tmp1;
        }
    }
}

int main()
{
    time_t start = clock();
    vector<vector<int>> b(30);
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            int x;
            cin >> x;
            b[i].push_back(x);
        }
    }
    // 無向グラフを作る
    //  x,y,値
    for (int i = 0; i < 30 - 1; i++)
    {
        for (int j = 1; j < i; j++)
        {
            g[{i, j, b[i][j]}].push_back({i + 1, j, b[i + 1][j]});
            g[{i, j, b[i][j]}].push_back({i + 1, j + 1, b[i + 1][j + 1]});
            g[{i, j, b[i][j]}].push_back({i, j + 1, b[i][j + 1]});
            // 逆も
            g[{i + 1, j, b[i + 1][j]}].push_back({i, j, b[i][j]});
            g[{i + 1, j + 1, b[i + 1][j + 1]}].push_back({i, j, b[i][j]});
            g[{i, j + 1, b[i][j + 1]}].push_back({i, j, b[i][j]});
        }
    }

    // 適当に頂点を選んで、隣接している頂点とswapして、valが小さい方がyが小さいようにする
    vector<vector<int>> ans;
    while (true)
    {
        tuple<int, int, int> v;
        int y = rand() % 30;
        int x = rand() % (y + 1);
        int val = b[y][x];
        v = {y, x, val};

        for (auto &i : g[v])
        {
            if (get<0>(v) > get<0>(i) && get<2>(v) < get<2>(i))
            {
                ans.push_back({get<0>(v), get<1>(v), get<0>(i), get<1>(i)});
                vertex_swap(v, i);
                break;
            }
            else if (get<0>(v) < get<0>(i) && get<2>(v) > get<2>(i))
            {
                ans.push_back({get<0>(v), get<1>(v), get<0>(i), get<1>(i)});
                vertex_swap(v, i);
                break;
            }
        }
        if (clock() - start > 1.9 * CLOCKS_PER_SEC)
            break;
    }

    int size = ans.size();
    cout << size << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << "\n";
    }
}