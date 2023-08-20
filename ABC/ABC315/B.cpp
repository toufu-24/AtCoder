#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
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
    int sum = accumulate(all(D), 0);
    int middle = sum / 2;

    int now = 0;
    for (int i = 0; i < M; i++)
    {
        if (now + D[i] > middle)
        {
            cout << i + 1 << " " << middle - now + 1 << endl;
            return 0;
        }
        now += D[i];
    }
    cout << M << " " << middle - now << endl;
}