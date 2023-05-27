#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> a(M, vector<int>(N));
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    vector<set<int>> s(N);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            s[a[i][j]].insert(a[i][j + 1]);
            s[a[i][j + 1]].insert(a[i][j]);
        }
    }

    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;
            if (!s[i].count(j))
            {
                cnt++;
            }
        }
    }
    cout << cnt/2 << endl;
}