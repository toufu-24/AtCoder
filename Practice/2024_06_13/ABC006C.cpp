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
    int N, M;
    cin >> N >> M;
    int adult = 0, child = 0, old = 0;
    adult = M / 2;
    if (M % 2 == 1)
    {
        old = 1;
        adult--;
    }
    // これで最大人数
    if (adult + old < N)
    {
        cout << -1 << " " << -1 << " " << -1 << endl;
        return 0;
    }
    // 最少人数はadult/2 + old
    if (adult / 2 + adult % 2 + old > N)
    {
        cout << -1 << " " << -1 << " " << -1 << endl;
        return 0;
    }

    // midがchild
    int want_legs = adult * 2;
    int want_people = N - old;
    int low = 0, up = adult;
    while (abs(low - up) > 1)
    {
        int mid = (low + up) / 2;
        int adult_mid = want_people - mid;
        if (mid * 4 + adult_mid * 2 <= want_legs)
        {
            low = mid;
        }
        else
        {
            up = mid;
        }
    }
    child = low;
    adult = want_people - child;
    cout << adult << " " << old << " " << child << endl;
    assert(adult * 2 + child * 4 + old * 3 == M);
    assert(adult + child + old == N);
}
