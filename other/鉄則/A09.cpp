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
    int H, W, N;
    cin >> H >> W >> N;
    vector<vector<int>> mass(H + 2, vector<int>(W + 2, 0));
    for (int i = 0; i < N; i++)
    {
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        mass[A][B]++;
        mass[C + 1][D + 1]++;
        mass[A][D + 1]--;
        mass[C + 1][B]--;
    }
    for (int i = 1; i <= H; i++)
    {
        for (int j = 2; j <= W; j++)
        {
            mass[i][j] += mass[i][j - 1];
        }
    }
    for (int i = 1; i <= W; i++)
    {
        for (int j = 2; j <= H; j++)
        {
            mass[j][i] += mass[j - 1][i];
        }
    }
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cout << mass[i][j] << " ";
        }
        cout << "\n";
    }
}