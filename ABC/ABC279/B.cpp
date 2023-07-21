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
    string S, T;
    cin >> S >> T;
    for (int i = 0; i < S.size(); i++)
    {
        for (int j = i; j < S.size(); j++)
        {
            string s_small;
            for (int k = i; k <= j; k++)
            {
                s_small += S[k];
            }
            if (s_small == T)
            {
                cout << "Yes";
                return 0;
            }
        }
    }
    cout << "No";
}