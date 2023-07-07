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
    vector<string> S(H);
    for (int i = 0; i < H; i++)
        cin >> S[i];

    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    if (S[0][0] != 's')
    {
        cout << "No";
        return 0;
    }

    string purpose = "snuke";
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    visited[0][0] = true;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        int x = get<0>(p);
        int y = get<1>(p);
        int purpose_index = get<2>(p) + 1;
        if (purpose_index == 5)
        {
            purpose_index = 0;
        }
        for (int i = 0; i < 4; i++)
        {
            int delta_x = dx[i];
            int delta_y = dy[i];

            int next_x = x + delta_x;
            int next_y = y + delta_y;
            if (next_x >= W || next_y >= H || next_x < 0 || next_y < 0)
                continue;
            if (visited[next_y][next_x])
                continue;
            if (S[next_y][next_x] != purpose[purpose_index])
                continue;

            visited[next_y][next_x] = true;
            q.push({next_x, next_y, purpose_index});
        }

        if (visited[H - 1][W - 1])
        {
            cout << "Yes";
            return 0;
        }
    }
    if (visited[H - 1][W - 1])
    {
        cout << "Yes";
        return 0;
    }
    cout << "No";
}