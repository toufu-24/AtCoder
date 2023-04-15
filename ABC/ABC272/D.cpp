#include <bits/stdc++.h>
using namespace std;
int N, M;
int cnt = 0;
vector<vector<int>> ans;

void distance(int cnt)
{
    double sq = sqrt(M);
    vector<pair<int, int>> before;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (ans[i][j] == cnt)
            {
                before.push_back(make_pair(i, j));
            }
        }
    }
    bool flag = false;

    for (int bf = 0; bf < before.size(); bf++)
    {
        int first = before[bf].first;
        int second = before[bf].second;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (ans[i][j] == -1)
                {
                    if (hypot(i - first, j - second) == sq)
                    {
                        ans[i][j] = cnt + 1;
                    }
                    flag = true;
                }
            }
        }
    }
    cnt++;
    if (flag)
        distance(cnt);
    else
    {
        return;
    }
}

int main()
{
    cin >> N >> M;
    ans.resize(N);
    for (int i = 0; i < N; i++)
    {
        ans[i].resize(N, -1);
    }
    ans[0][0] = 0;
    distance(0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
}