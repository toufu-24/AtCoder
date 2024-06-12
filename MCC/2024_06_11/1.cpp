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

vector<int> f(int N)
{
    if (N == 1)
    {
        return {1};
    }
    vector<int> ret;
    auto f1 = f(N - 1);
    ret.insert(ret.end(), all(f1));
    ret.push_back(N);
    ret.insert(ret.end(), all(f1));
    return ret;
}

int32_t main()
{
    int N;
    cin >> N;
    vector<int> ans = f(N);
    for(auto x: ans)
    {
        cout << x << " ";
    }
}
