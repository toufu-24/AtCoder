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
    map<int, int> cnt;
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int order;
        cin >> order;
        switch (order)
        {
            int x;
        case 1:
            cin >> x;
            cnt[x]++;
            break;
        case 2:
            int c;
            cin >> x >> c;
            cnt[x] -= c;
            if (cnt[x] <= 0)
            {
                cnt.erase(x);
            }
            break;
        case 3:
            int max = cnt.rbegin()->first;
            int min = cnt.begin()->first;
            cout << max - min << endl;
            break;
        }
    }
}
