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
    string tmp, T;
    cin >> tmp >> T;
    long double t = 0;
    t = int(T[0] - '0');
    for (int i = 1; i < T.size(); i++)
    {
        t = t * 10000;
        t = t / double(T[i] - '0');
    }

    for (int i = 0; i < T.size() + 1; i++)
    {
        string S = tmp.substr(0, i) + tmp.substr(tmp.length() - T.length() + i);
        bool flag = false;
        long double s = int(S[0] - '0');
        for (int i = 1; i < S.size(); i++)
        {
            s = s * 10000;
            s = s / double(S[i] - '0');
        }

        if (s < t + 0.001 && s > t - 0.001)
        {
            flag = true;
        }
        if (flag)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
}