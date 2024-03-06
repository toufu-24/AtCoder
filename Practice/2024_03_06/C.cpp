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

#define int ll

int32_t main()
{
    string s;
    cin >> s;
    bool weak = true;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != s[0])
        {
            weak = false;
            break;
        }
    }
    if (weak)
    {
        cout << "Weak" << endl;
        return 0;
    }

    weak = true;
    int now = s[0] - '0';
    for (int i = 1; i < s.size(); i++)
    {
        now = (now + 1) % 10;
        if (now != s[i] - '0')
        {
            weak = false;
            break;
        }
    }

    cout << (weak ? "Weak" : "Strong") << endl;
}