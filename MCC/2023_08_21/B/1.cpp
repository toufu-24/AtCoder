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
    modint::set_mod(998244353);
    ll N, K;
    cin >> N >> K;
    set<int> ng;
    map<int, pair<char, int>> mp;
    for (int i = 0; i < K; i++)
    {
        char c;
        int k;
        cin >> c >> k;
        k--;
        mp[i] = make_pair(c, k);
        ng.insert(k);
    }
    modint ans = 1;
    for (int i = 0; i < N; i++)
    {
        if (ng.count(i))
            continue;
        int able_place = 0;
        for (int j = 0; j < K; j++)
        {
            if (mp[j].first == 'L')
            {
                if (i > mp[j].second)
                {
                    able_place++;
                }
            }
            else
            {
                if (i < mp[j].second)
                {
                    able_place++;
                }
            }
        }
        ans *= able_place;
    }
    cout << ans.val() << endl;
}