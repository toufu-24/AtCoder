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
    int N, Q;
    cin >> N >> Q;
    deque<pair<int, int>> deq;
    for (int i = 0; i < N; i++)
    {
        deq.push_back({i + 1, 0});
    }

    while (Q--)
    {
        int o;
        cin >> o;
        if (o == 1)
        {
            char C;
            cin >> C;
            int f_x = deq.front().first;
            int f_y = deq.front().second;
            switch (C)
            {
            case 'R':
                deq.push_front({f_x + 1, f_y});
                break;
            case 'L':
                deq.push_front({f_x - 1, f_y});
                break;
            case 'U':
                deq.push_front({f_x, f_y + 1});
                break;
            case 'D':
                deq.push_front({f_x, f_y - 1});
                break;
            default:
                break;
            }
            deq.pop_back();
        }
        else
        {
            int p;
            cin >> p;
            cout << deq[p - 1].first << " " << deq[p - 1].second << endl;
        }
    }
}
