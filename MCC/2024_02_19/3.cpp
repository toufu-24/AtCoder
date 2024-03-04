#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, D, K;
        cin >> N >> D >> K;
        int x = 0;
        vector<bool> colored(N, false);
        colored[0] = true;
        for (int i = 1; i < K; i++)
        {
            x = (x + D) % N;
            while (colored[x])
            {
                x = (x + 1) % N;
            }
            colored[x] = true;
        }
        cout << x << endl;
    }
}