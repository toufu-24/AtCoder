#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    string S;
    cin >> S;
    string ans;
    for (int i = 0; i < S.size(); i++)
    {
        ans += S[i];
        while (true)
        {
            if (ans.size() < 3)
            {
                break;
            }
            string ABC = ans.substr(ans.size() - 3, 3);
            if (ABC == "ABC")
            {
                ans.pop_back();
                ans.pop_back();
                ans.pop_back();
            }
            else
            {
                break;
            }
        }
    }
    cout << ans << endl;
}