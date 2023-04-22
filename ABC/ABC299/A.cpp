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
    cin >> N;
    string S;
    cin >> S;
    bool flag = false;
    for (int i = 0; i < N; i++)
    {
        if (flag)
        {
            if (S[i] == '*')
            {
                cout << "in";
                return 0;
            }
            else if (S[i] == '|')
            {
                flag = false;
                break;
            }
        }
        if (S[i] == '|')
        {
            flag = true;
        }
    }
    cout << "out";
}