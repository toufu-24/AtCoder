#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int M;
    cin >> M;
    vector<int> D(M);
    for (int i = 0; i < M; i++)
    {
        cin >> D[i];
    }
    int sum = (reduce(all(D)) + 1) / 2;
    int now = 0;
    for (int i = 0; i < M; i++)
    {
        if (now + D[i] >= sum)
        {
            cout << i + 1 << " " << sum - now << endl;
            return 0;
        }
        now += D[i];
    }
    cout << M << " " << sum - now << endl;
}