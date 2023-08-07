#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    map<int, bool> mp;
    for (int i = 1; i <= 2 * N + 1; i++)
    {
        mp[i] = false;
    }
    cout << 1 << endl;
    mp[1] = true;

    while (true)
    {
        int opponent;
        cin >> opponent;
        if (opponent == 0)
        {
            return 0;
        }
        mp[opponent] = true;
        int next;
        for (int i = 1; i <= 2 * N + 1; i++)
        {
            if (!mp[i])
            {
                next = i;
                break;
            }
        }
        mp[next] = true;
        cout << next << endl;
    }
}