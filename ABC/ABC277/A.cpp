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
    int N, X;
    cin >> N >> X;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        if (P[i] == X)
        {
            cout << i + 1 << endl;
            return 0;
        }
    }
}