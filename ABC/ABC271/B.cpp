#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> list(N);
    for (int i = 0; i < N; i++)
    {
        int L;
        cin >> L;
        for (int j = 0; j < L; j++)
        {
            int tmp;
            cin >> tmp;
            list[i].push_back(tmp);
        }
    }
    vector<pair<int, int>> st(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> st[i].first;
        cin >> st[i].second;
        cout << list[st[i].first - 1][st[i].second - 1] << endl;
    }
}