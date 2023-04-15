#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int64_t G[200000][200000];

int main()
{
    int N, M;
    cin >> N >> M;
    dsu d(N);
    for (int i = 0; i < M; i++)
    {
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        tmp1--;
        tmp2--;
        G[tmp1][tmp2]++;
        if (tmp1 != tmp2)
            G[tmp2][tmp1]++;
        d.merge(tmp1, tmp2);
    }
    if (N != M)
    {
        cout << "No";
        return 0;
    }
    vector<vector<int>> sep;
    sep = d.groups();
    int sep_size = sep.size();
    bool ans = true;
    for (int i = 0; i < sep_size; i++)
    {
        int size = sep[i].size();
        int cnt = 0;
        for (int j = 0; j < size; j++)
        {
            for (int k = j; k < size; k++)
            {
                cnt += G[sep[i][j]][sep[i][k]];
            }
        }
        if (cnt != size)
        {
            ans = false;
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
    return 0;
}