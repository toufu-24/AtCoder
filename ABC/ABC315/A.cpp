#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

char ng[] = {'a', 'i', 'u', 'e', 'o'};

int main()
{
    string S;
    cin >> S;
    for (int i = 0; i < S.size(); i++)
    {
        bool ok = true;
        for (int j = 0; j < 5; j++)
        {
            if (S[i] == ng[j])
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            cout << S[i];
        }
    }
}