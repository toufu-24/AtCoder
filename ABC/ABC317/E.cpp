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
    int H, W;
    cin >> H >> W;
    vector<string> A(H);
    for (int i = 0; i < H; i++)
    {
        cin >> A[i];
    }
    pair<int, int> start, goal;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            switch (A[i][j])
            {
            case 'S':
                start = make_pair(i, j);
                break;
            case 'G':
                goal = make_pair(i, j);
                break;
            case '>':
                for (int k = j + 1; k < W; k++)
                {
                    if (A[i][k] != '.' && A[i][k] != '!')
                    {
                        break;
                    }
                    A[i][k] = '!';
                }
                break;
            case '<':
                for (int k = j - 1; k >= 0; k--)
                {
                    if (A[i][k] != '.' && A[i][k] != '!')
                    {
                        break;
                    }
                    A[i][k] = '!';
                }
                break;
            case '^':
                for (int k = i - 1; k >= 0; k--)
                {
                    if (A[k][j] != '.' && A[k][j] != '!')
                    {
                        break;
                    }
                    A[k][j] = '!';
                }
                break;
            case 'v':
                for (int k = i + 1; k < H; k++)
                {
                    if (A[k][j] != '.' && A[k][j] != '!')
                    {
                        break;
                    }
                    A[k][j] = '!';
                }
                break;
            default:
                break;
            }
        }
    }
    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> q;
    q.push(start);
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    dist[start.first][start.second] = 0;
    while (!q.empty())
    {
        int nx = q.front().first;
        int ny = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int next_x = nx + dx[i];
            int next_y = ny + dy[i];
            if (next_x < 0 || next_x >= H || next_y < 0 || next_y >= W)
            {
                continue;
            }
            if (A[next_x][next_y] == '#' || A[next_x][next_y] == '!' || A[next_x][next_y] == '<' || A[next_x][next_y] == '>' || A[next_x][next_y] == '^' || A[next_x][next_y] == 'v')
            {
                continue;
            }
            if (dist[next_x][next_y] != -1)
            {
                continue;
            }
            dist[next_x][next_y] = dist[nx][ny] + 1;
            q.push(make_pair(next_x, next_y));
        }
    }
    cout << dist[goal.first][goal.second];
}