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
    int N, Q;
    cin >> N >> Q;
    deque<pair<int, int>> dragon;
    for (int i = 1; i <= N; i++)
    {
        dragon.push_back({i, 0});
    }

    while (Q--)
    {
        int num;
        cin >> num;
        switch (num)
        {
        case 1:
            char C;
            cin >> C;
            int x, y;
            tie(x, y) = dragon.front();
            switch (C)
            {
            case 'R':
                dragon.push_front({x + 1, y});
                break;
            case 'L':
                dragon.push_front({x - 1, y});
                break;
            case 'U':
                dragon.push_front({x, y + 1});
                break;
            case 'D':
                dragon.push_front({x, y - 1});
                break;
            default:
                break;
            }
            dragon.pop_back();
            break;

        case 2:
            int p;
            cin >> p;
            cout << dragon[p - 1].first << " " << dragon[p - 1].second << endl;
        default:
            break;
        }
    }
}