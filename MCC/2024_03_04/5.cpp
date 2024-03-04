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

struct edge
{
    int cost;
    pair<int, int> to;
};

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {H - 1, W - 1};
    map<pair<int, int>, vector<edge>> graph;
    int dx3[] = {1, 1, 0};
    int dy3[] = {0, 1, 1};
    int dx4[] = {1, 0, -1, 0};
    int dy4[] = {0, 1, 0, -1};
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '#')
            {
                for (int d = 0; d < 3; d++)
                {
                    int nx = i + dx3[d];
                    int ny = j + dy3[d];
                    if (nx < H && ny < W)
                    {
                        graph[{i, j}].push_back({0, {nx, ny}});
                    }
                }
            }
        }
    }
}