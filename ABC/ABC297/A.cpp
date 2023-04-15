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
    int N, D;
    cin >> N >> D;
    vector<int> T(N);
    for (int i = 0; i < N; i++)
    {
        cin >> T[i];
    }
    for (int i = 1; i < N; i++)
    {
        if (T[i] - T[i - 1] <= D)
        {
            cout << T[i] << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}