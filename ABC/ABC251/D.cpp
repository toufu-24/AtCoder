#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int W;
    cin >> W;
    // 3桁で1e6を表せる進数
    // 100進数で表す
    vector<int> ans;
    for (int i = 1; i < 100; i++)
    {
        ans.push_back(i);
        ans.push_back(i * 100);
        ans.push_back(i * 10000);
    }
    cout << ans.size() << endl;
    for (auto x : ans)
    {
        cout << x << " ";
    }
}