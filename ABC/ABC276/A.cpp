#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    string s;
    cin >> s;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] == 'a')
        {
            cout << i + 1;
            return 0;
        }
    }
    cout << -1;
    return 0;
}