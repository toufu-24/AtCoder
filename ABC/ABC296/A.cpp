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
    bool flag = true;
    for (int i = 1; i < N; i++)
    {
        if (!((S[i - 1] == 'M' && S[i] == 'F') || (S[i - 1] == 'F' && S[i] == 'M')))
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
