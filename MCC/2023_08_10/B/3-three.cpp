#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int hyouka(const int &leader, const string &S)
{
    int N = S.size();
    int right_count = 0;
    for (int i = leader + 1; i < N; i++)
    {
        if (S[i] == 'E')
        {
            right_count++;
        }
    }
    int left_count = 0;
    for (int i = leader - 1; i >= 0; i--)
    {
        if (S[i] == 'W')
        {
            left_count++;
        }
    }
    return right_count + left_count;
}

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;

    int left = 0;
    int right = N;
    while (abs(right - left) > 2)
    {
        int c1 = (left * 2 + right) / 3;
        int c2 = (left + right * 2) / 3;
        if (hyouka(c1, S) > hyouka(c2, S))
        {
            right = c2;
        }
        else
        {
            left = c1;
        }
    }
    int ans = 1e9;
    for (int i = left; i <= right; i++)
    {
        ans = min(ans, hyouka(i, S));
    }
    cout << ans << endl;
}