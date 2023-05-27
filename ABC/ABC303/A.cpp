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
    int N;
    string S, T;
    cin >> N >> S >> T;
    bool ans = true;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'l' && T[i] == '1')
        {
            continue;
        }
        else if (T[i] == 'l' && S[i] == '1')
        {
            continue;
        }
        else if (S[i] == 'o' && T[i] == '0')
        {
            continue;
        }
        else if (T[i] == 'o' && S[i] == '0')
        {
            continue;
        }
        else if (S[i] == T[i])
        {
            continue;
        }
        else
        {
            ans = false;
            break;
        }
    }
    if (ans)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}