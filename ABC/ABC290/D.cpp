#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N, D, K;
        cin >> N >> D >> K;
        int x = 0;
        vector<bool> mass(N, false);
        for (int i = 0; i < K; i++)
        {
            x = (x + D) % N;
            if (i == 0)
            {
                x = 0;
            }
            while (mass[x])
            {
                x = (x + 1) % N;
            }
            mass[x] = true;
        }
        cout << x << endl;
    }
}