#include <bits/stdc++.h>
using namespace std;

int main()
{
    int64_t N, M, time;
    cin >> N >> M >> time;
    vector<int> room(N, 0);
    for (int i = 1; i < N; i++)
    {
        cin >> room[i];
    }
    map<int, int> bonus;
    for (int i = 1; i <= M; i++)
    {
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        bonus[tmp1] = tmp2;
    }
    bool flag = true;
    for (int i = 1; i < N; i++)
    {
        time += bonus[i];
        time -= room[i];
        if (time <= 0)
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}