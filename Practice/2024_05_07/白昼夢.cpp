#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    bool ok = true;
    for (int i = 0; i < S.size(); i++)
    {
        string five = S.substr(i, 5);
        string six = S.substr(i, 6);
        string seven = S.substr(i, 7);
        string ten = S.substr(i, 10);
        if (ten == "dreamerase")
        {
            i += 4;
        }
        else if (six == "eraser")
        {
            i += 5;
        }
        else if (seven == "dreamer")
        {
            i += 6;
        }
        else if (five == "dream" || five == "erase")
        {
            i += 4;
        }
        else
        {
            ok = false;
            break;
        }
    }
    if (ok)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
