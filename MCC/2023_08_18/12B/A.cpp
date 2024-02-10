#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

bool isKaibun(string S)
{
    string rS = S;
    reverse(rS);
    return S == rS;
}

int main()
{
    string S;
    cin >> S;
    if (isKaibun(S))
    {
        cout << "Yes" << endl;
        return 0;
    }
    reverse(S);
    int left_a = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == 'a')
        {
            left_a++;
        }
        else
        {
            break;
        }
    }
    int right_a = 0;
    for (int i = S.size() - 1; i >= 0; i--)
    {
        if (S[i] == 'a')
        {
            right_a++;
        }
        else
        {
            break;
        }
    }

    int able_incresase = left_a - right_a;
    while (able_incresase > 0)
    {
        S += 'a';
        able_incresase--;
    }
    if (isKaibun(S))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}