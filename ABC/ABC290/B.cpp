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
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (cnt < K)
        {
            if (S[i] == 'o')
            {
                cnt++;
            }
        }
        else
        {
            S[i] = 'x';
        }
    }
    cout << S << endl;
}