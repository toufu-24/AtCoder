#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    string S;
    cin >> S;
    int cnt = S.size();
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == '0' && S[i + 1] == '0')
        {
            cnt--;
            i++;
        }
    }
    cout << cnt;
}