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
    int H, W;
    cin >> H >> W;
    for (int i = 0; i < H; i++)
    {
        string S;
        vector<int> A(W);
        for (int j = 0; j < W; j++)
        {
            cin >> A[j];
            if (A[j] == 0)
            {
                S += '.';
            }
            else
            {
                S += char(A[j] + 'A' -1);
            }
        }
        cout << S << endl;
    }
}