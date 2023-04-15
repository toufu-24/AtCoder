#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

map<int64_t, int64_t> memo;

int64_t func(int64_t N)
{
    if (N == 0)
    {
        return 1;
    }
    int64_t two = N / 2;
    if (!memo.count(two))
    {
        memo[two] = func(two);
    }
    int64_t three = N / 3;
    if (!memo.count(three))
    {
        memo[three] = func(three);
    }
    return memo[two] + memo[three];
}

int main()
{
    int64_t N;
    cin >> N;
    cout << func(N);
}