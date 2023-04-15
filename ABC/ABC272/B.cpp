#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    bool ans = true;
    vector<vector<int>> data(M);
    for (int i = 0; i < M; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int tmp;
            cin >> tmp;
            data[i].push_back(tmp);
        }
    }
    sort(data.begin(), data.end());
    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            bool flag = false;
            for (int k = 0; k < M; k++)
            {
                bool flag1 = false, flag2 = false;
                for (int l = 0; l < data[k].size(); l++)
                {
                    if (data[k][l] == i)
                    {
                        flag1 = true;
                    }
                    else if (data[k][l] == j)
                    {
                        flag2 = true;
                    }
                    if (flag1 && flag2)
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                {
                    break;
                }
            }
            if (!flag)
                ans = false;
            if (!ans)
            {
                break;
            }
        }
        if (!ans)
        {
            break;
        }
    }
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}