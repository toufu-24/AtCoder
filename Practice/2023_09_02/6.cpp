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
    int N;
    cin >> N;
    string S;
    cin >> S;
    map<char, int> left;
    map<char, int> right;
    for (int i = 0; i < N; i++)
    {
        right[S[i]]++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        left[S[i]]++;
        right[S[i]]--;
        if (right[S[i]] == 0)
        {
            right.erase(S[i]);
        }
        int common = 0;
        for (auto l : left)
        {
            if (right.count(l.first))
            {
                common++;
            }
        }
        ans = max(ans, common);
    }
    cout << ans;
}