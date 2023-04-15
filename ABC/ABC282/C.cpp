#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (cnt % 2 == 0 && S[i] == ',')
        {
            S[i] = '.';
        }
        if (S[i] == '"')
        {
            cnt++;
        }
    }
    cout << S;
}