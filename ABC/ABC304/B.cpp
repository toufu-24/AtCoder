#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N;
    cin >> N;
    string st_N = to_string(N);
    ll size = st_N.size();
    string S;
    S += st_N[0];
    if (st_N.size() > 1)
    {
        S += st_N[1];
    }
    if (st_N.size() > 2)
    {
        S += st_N[2];
    }
    for (int i = 0; i < size - 3; i++)
    {
        S += "0";
    }
    std::cout << S << endl;
}