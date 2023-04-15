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
    int a = 110000000;
    while (true)
    {
        if (a > 1000000000)
        {
            break;
        }
        string S = to_string(a);
        if (S[0] == S[1] && S[4] == S[5] && S[6] == S[8] && S[2] == '0' && S[3] == '0' && S[7] == '0')
        {
            cout << S << ",";
        }
        a++;
    }
}