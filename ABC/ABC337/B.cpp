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
    string S;
    cin >> S;
    char c[3] = {'A', 'B', 'C'};
    int cnt[3] = {0, 0, 0};
    int now = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == c[now])
        {
            cnt[now]++;
        }
        else
        {
            now++;
            i--;
            if (now >= 3)
            {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
}