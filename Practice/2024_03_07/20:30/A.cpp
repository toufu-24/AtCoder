#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    vector<int> num(3);
    for (int i = 0; i < 3; i++)
    {
        cin >> num[i];
    }
    auto s = num;
    SORT(s);
    if (s[1] == num[1])
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}