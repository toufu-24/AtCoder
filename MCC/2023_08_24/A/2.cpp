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
    int N;
    cin >> N;
    vector<int> H(N);
    for (int i = 0; i < N; i++)
    {
        cin >> H[i];
    }

    int maximum = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        int cnt = 0;
        while (i > 0 && H[i] <= H[i - 1])
        {
            cnt++;
            i--;
        }
        maximum = max(maximum, cnt);
    }
    cout << maximum << endl;
}