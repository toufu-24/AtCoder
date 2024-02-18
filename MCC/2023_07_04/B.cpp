#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        int N;
        cin >> N;
        if (N == 0)
        {
            break;
        }
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        vector<pair<int, int>> goal(N + 1);
        for (int i = 0; i < N + 1; i++)
        {
            cin >> goal[i].first >> goal[i].second;
        }
        // 安全地帯までの距離
        vector<int> safe_dist(N + 1);
        for (int i = 0; i <= N; i++)
        {
            int x = goal[i].first;
            int y = goal[i].second;
            if (x < A)
            {
                if (y < B)
                {
                    safe_dist[i] = A - x + B - y;
                }
                else if (D < y)
                {
                    safe_dist[i] = A - x + y - D;
                }
                else
                {
                    safe_dist[i] = A - x;
                }
            }
            else if (C < x)
            {
                if (y < B)
                {
                    safe_dist[i] = x - C + B - y;
                }
                else if (D < y)
                {
                    safe_dist[i] = x - C + y - D;
                }
                else
                {
                    safe_dist[i] = x - C;
                }
            }
            else
            {
                if (y < B)
                {
                    safe_dist[i] = B - y;
                }
                else if (D < y)
                {
                    safe_dist[i] = y - D;
                }
                else
                {
                    safe_dist[i] = 0;
                }
            }
        }

        // 解を求める
        int64_t damage = 0;
        for (int i = 1; i <= N; i++)
        {
            int now_x = goal[i - 1].first;
            int now_y = goal[i - 1].second;
            int next_x = goal[i].first;
            int next_y = goal[i].second;
            int dist = abs(now_x - next_x) + abs(now_y - next_y);
            if (safe_dist[i - 1] != 0)
            {
                damage += min(dist, safe_dist[i - 1] - 1 + safe_dist[i]);
            }
            else
            {
                damage += min(dist, safe_dist[i - 1] + safe_dist[i]);
            }
        }
        cout << damage << "\n";
    }
}