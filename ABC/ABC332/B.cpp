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
    int K, G, M;
    cin >> K >> G >> M;
    int glass = 0, cup = 0;
    for (int i = 0; i < K; i++)
    {
        if (glass == G)
        {
            glass = 0;
        }
        else if (cup == 0)
        {
            cup = M;
        }
        else
        {
            int now_glass = glass;
            glass = min(G, glass + cup);
            cup = max(0, cup - (G - now_glass));
        }
    }
    cout << glass << " " << cup << endl;
}