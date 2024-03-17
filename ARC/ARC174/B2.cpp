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
    int t;
    cin >> t;
    while (t--)
    {
        int less = 0;
        vector<int> A(5);
        for (int i = 0; i < 5; i++)
        {
            cin >> A[i];
            less += A[i] * (3 - (i + 1));
        }
        vector<int> P(5);
        for (int i = 0; i < 5; i++)
        {
            cin >> P[i];
        }
        // 評価1,2,3は選ぶ価値ない
        int minimum = 1e18;
        vector<ld> efficient(5, -1e18); // 1円あたりの平均への寄与
        for (int i = 3; i < 5; i++)
        {
            efficient[i] = ((i + 1) - 3) / (ld)P[i];
        }
        // 4,5を比較して4を選ぶか5を選ぶか
        // lessだけ
        int five = 0;
        int ng = -1;
        int ok = 1e18;
        while (ok - ng > 1)
        {
            int mid = (ok + ng) / 2;
            if (mid * 2 >= less)
            {
                ok = mid;
            }
            else
            {
                ng = mid;
            }
        }
        five = (ok - 1) * P[4];
        int five_five = five + P[4];
        int five_four = five + P[3];
        if ((ok - 1) * 2 + 1 < less)
        {
            five_four += P[3];
        }
        int four = 0;
        four = less * P[3];
        minimum = max(min({five_five, five_four, four}), int(0));
        cout << minimum << endl;
    }
}
