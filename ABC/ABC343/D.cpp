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
    int N, T;
    cin >> N >> T;
    vector<int> senshu(N, 0);
    map<int, int> mp;
    mp[0] = N;
    for (int i = 0; i < T; i++)
    {
        int A, B;
        cin >> A >> B;
        A--;
        int point = senshu[A];
        mp[point]--;
        if (mp[point] == 0)
        {
            mp.erase(point);
        }
        point += B;
        senshu[A] = point;
        mp[point]++;
        cout << mp.size() << endl;
    }
}