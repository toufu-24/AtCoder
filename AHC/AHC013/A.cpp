#include <bits/stdc++.h>
using namespace std;

int x_count = 0, y_count = 0;

// l・・・左  r・・・右  u・・・上  d・・・下
int go(vector<vector<int>> before, int i, int j, char word)
{
    if (word == 'l')
    {
        if (before[i][j] == 0)
            return j;
        while (before[i][j - 1] == 0 && j != 0)
        {
            before[i][j - 1] = before[i][j];
            before[i][j] = 0;
            j--;
            x_count++;
        }
        return j;
    }
    else if (word == 'r')
    {
        if (before[i][j] == 0)
            return j;
        while (before[i][j + 1] == 0 && j != 0)
        {
            before[i][j + 1] = before[i][j];
            before[i][j] = 0;
            j++;
            x_count++;
        }
        return j;
    }
    else if (word == 'u')
    {
        if (before[i][j] == 0)
            return i;
        while (before[i - 1][j] == 0 && i != 0)
        {
            before[i - 1][j] = before[i][j];
            before[i][j] = 0;
            i--;
            x_count++;
        }
        return i;
    }
    else if (word == 'd')
    {
        if (before[i][j] == 0)
            return i;
        while (before[i + 1][j] == 0 && i != 0)
        {
            before[i + 1][j] = before[i][j];
            before[i][j] = 0;
            i++;
            x_count++;
        }
        return i;
    }
}

void connect(vector<vector<int>> &before, int i, int j)
{
}

//添え字が同じなら接続可能
int main(void)
{
    int N, K; // K=2かつ15≤N≤39  K=3かつ18≤N≤42  K=4かつ21≤N≤45  K=5かつ24≤N≤48
    cin >> N >> K;
    vector<vector<int>> before(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> before[i][j];

    vector<vector<int>> after(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            after[i][j] = before[i][j];
    pair<int, int> after_place;
    if (K == 2)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                if (before[i][j] == 1)
                    after_place.second = go(before, i, j, 'l');
                else if (before[i][j] == 2)
                    after_place.second = go(before, i, j, 'r');
            }
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                if (before[j][i] == 1)
                    after_place.first = go(before, i, j, 'u');
                else if (before[j][i] == 2)
                    after_place.first = go(before, i, j, 'd');
            }
        }
    }

    //出力
    cout << x_count;
    for (int i = 0; i < x_count; i++)
    {
    }
    cout << y_count;
    for (int i = 0; i < y_count; i++)
    {
        /* code */
    }
}