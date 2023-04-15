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
    int agree = 0;
    for (int i = 0; i < N; i++)
    {
        string S;
        cin >> S;
        if (S == "For")
        {
            agree++;
        }
    }
    if (agree * 2 >= N)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}