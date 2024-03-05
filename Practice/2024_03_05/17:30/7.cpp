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
    int W;
    cin >> W;
    // W = 1e6だけ考えればよさそう
    // 100進数でいい
    vector<int> weight;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 1; j <= 100; j++)
        {
            weight.push_back(j * powl(100, i));
        }
    }

    cout << weight.size() << endl;
    for (int i = 0; i < weight.size(); i++)
    {
        cout << weight[i] << " ";
    }
}