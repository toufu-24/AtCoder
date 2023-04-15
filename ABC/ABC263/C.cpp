#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    vector<tuple<int, int, int, int, int, int, int, int, int, int>> num_line;
    vector<int> tmp(10, 9999);
    for (int i = 0; i < N; i++)
    {
        tmp[i] = i + 1;
    }

    while (1)
    {
        int i;
        num_line.push_back(make_tuple(tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], tmp[6], tmp[7], tmp[8], tmp[9]));
        if (tmp[0] == M - N + 1 && tmp[N - 1] == M)
            break;
        int count = 0;
        for (i = N - 1; 0 <= i; i--)
        {
            if (tmp[i] != M - count)
            {
                tmp[i]++;
                for (int j = i + 1; j < N; j++)
                {
                    tmp[j] = tmp[i] + j - i;
                }
                break;
            }
            count++;
        }
    }

    for (int i = 0; i < num_line.size(); i++)
    {
        int j = 0;
        tmp[j] = get<0>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<1>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<2>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<3>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<4>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<5>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<6>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<7>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<8>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        tmp[j] = get<9>(num_line[i]);
        if (tmp[j] != 9999)
        {
            cout << tmp[j++];
            cout << " ";
        }
        cout << endl;
    }

    return 0;
}