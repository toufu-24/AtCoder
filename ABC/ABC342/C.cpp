#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    map<char, char> mp;
    for (int i = 0; i < 26; i++)
    {
        mp['a' + i] = 'a' + i;
    }
    while (Q--)
    {
        char c, d;
        cin >> c >> d;
        for (int i = 0; i < 26; i++)
        {
            if (mp['a' + i] == c)
            {
                mp['a' + i] = d;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << mp[S[i]];
    }
}