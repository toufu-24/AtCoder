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
    set<string> S;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        bool set_flag = false;
        string tmp;
        cin >> tmp;
        if (!S.count(tmp))
        {
            cnt++;
            set_flag = true;
        }
        S.insert(tmp);
        reverse(tmp);
        if (!S.count(tmp) && !set_flag)
        {
            cnt++;
        }
        S.insert(tmp);
    }
    cout << cnt;
}