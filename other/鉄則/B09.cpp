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
    int N;
    cin >> N;
    vector<vector<int>> coodinate(1502, vector<int>(1502,0));
    for (int q = 0; q < N; q++)
    {
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        coodinate[A][B]++;
        coodinate[C + 1][D + 1]++;
        coodinate[A][D + 1]--;
        coodinate[C + 1][B]--;
    }
    // 累積和
    for (int i = 1; i <= 1500; i++)
    {
        for (int j = 2; j <= 1500; j++)
        {
            coodinate[i][j] += coodinate[i][j - 1];
        }
    }
    for (int i = 1; i <= 1500; i++)
    {
        for (int j = 2; j <= 1500; j++)
        {
            coodinate[j][i] += coodinate[j - 1][i];
        }
    }
    int cnt = 0;
    for (int i = 0; i < 1500; i++)
    {
        for (int j = 0; j < 1500; j++)
        {
            if (coodinate[i + 1][j + 1] != 0)
            {
                cnt++;
            }
        }
    }
    cout << cnt;
}