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
    ll N;
    cin >> N;
    int cnt = 0;
    int num = 110000000;
    num += (N / 100000) * 110000000;
    cnt += (N / 100000) * 100000;

    while (true)
    {
        if (N == 900000)
        {
            cout << 999999999;
            break;
        }
        else
        {
            string S = to_string(num);
            if (S[0] == S[1] && S[4] == S[5] && S[6] == S[8])
            {
                cnt++;
                if (cnt == N)
                {
                    cout << S;
                    break;
                }
            }
            num++;
        }
    }
}