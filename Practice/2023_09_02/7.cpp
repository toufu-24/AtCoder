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
    vector<int> color;
    for (int i = 0; i <= 3200; i += 400)
    {
        color.push_back(i);
    }
    color.push_back(1e9);
    int N;
    cin >> N;
    vector<int> a(N);
    map<int, int> mp;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        int idx = upper_bound(all(color), a[i]) - color.begin();
        mp[idx]++;
    }
    // 自由色
    if (mp.count(9))
    {
        if (mp.size() == 1)
        {
            cout << 1 << " " << mp[9] << endl;
        }
        else
        {
            cout << mp.size() - 1 << " " << mp.size() - 1 + mp[9] << endl;
        }
    }
    else
    {
        cout << mp.size() << " " << mp.size() << endl;
    }
}