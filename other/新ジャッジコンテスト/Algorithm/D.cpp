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
    int N1, N2, M;
    cin >> N1 >> N2 >> M;
    vector<vector<int>> G1(N1);
    vector<vector<int>> G2(N2);
    for (int i = 0; i < M; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x < N1)
        {
            x--;
            y--;
            G1[x].push_back(y);
            G1[y].push_back(x);
        }
        else
        {
            x--;
            y--;
            x -= N1;
            y -= N1;
            G2[x].push_back(y);
            G2[y].push_back(x);
        }
    }

    queue<int> q1;
    q1.push(0);
    vector<int> dist1(N1, -1);
    dist1[0] = 0;
    while (!q1.empty())
    {
        int now = q1.front();
        q1.pop();
        for (auto next : G1[now])
        {
            if (dist1[next] != -1)
                continue;
            dist1[next] = dist1[now] + 1;
            q1.push(next);
        }
    }
    int max_dist1 = *max_element(all(dist1));

    queue<int> q2;
    q2.push(N2 - 1);
    vector<int> dist2(N2, -1);
    dist2[N2 - 1] = 0;
    while (!q2.empty())
    {
        int now = q2.front();
        q2.pop();
        for (auto next : G2[now])
        {
            if (dist2[next] != -1)
                continue;
            dist2[next] = dist2[now] + 1;
            q2.push(next);
        }
    }
    int max_dist2 = *max_element(all(dist2));

    cout << max_dist1 + max_dist2 + 1;
}