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
    int Q;
    cin >> Q;
    map<int, int> mp;
    for (int q = 0; q < Q; q++)
    {
        int order;
        cin >> order;
        int x, c;
        switch (order)
        {
        case 1:
            cin >> x;
            mp[x]++;
            break;
        case 2:
            cin >> x >> c;
            mp[x] -= c;
            if (mp[x] <= 0)
            {
                mp.erase(x);
            }
            break;
        case 3:
            cout << mp.rbegin()->first - mp.begin()->first << endl;
            break;
        default:
            break;
        }
    }
}