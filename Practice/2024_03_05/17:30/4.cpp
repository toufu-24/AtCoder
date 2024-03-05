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
    int max_size = 1;
    for (int s = 0; s < S.size(); s++)
    {
        for (int e = s; e < S.size(); e++)
        {
            string sub = S.substr(s, e - s + 1);
            string rev = sub;
            REVERSE(rev);
            if (sub == rev)
            {
                max_size = max(max_size, (int)sub.size());
            }
        }
    }
    cout << max_size;
}