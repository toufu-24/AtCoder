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

#define int ll

vector<int> primeFactors(int N)
{
    vector<int> res;
    int orig = N;
    for (int i = 2; i * i <= orig; i++)
    {
        bool flag = false;
        while (N % i == 0)
        {
            res.push_back(i);
            N /= i;
            flag = true;
        }
        if (flag)
        {
            i = 2 - 1;
        }
    }
    if (N > 1)
    {
        res.push_back(N);
    }
    SORT(res);
    return res;
}

signed main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        vector<int> soinsuu = primeFactors(N);
        int cnt = 0;
        int sum = 0;
        int prev = soinsuu[0];
        int now = soinsuu[0];
        for (int i = 1; i < soinsuu.size(); i++)
        {
            if (prev == soinsuu[i])
            {
                now *= soinsuu[i];
            }
            else
            {
                cnt++;
                sum += now;
                prev = soinsuu[i];
                now = soinsuu[i];
            }
        }
        sum += now;
        cnt++;
        if (sum > N || cnt <= 1)
        {
            cout << "No\n";
        }
        else
        {
            cout << "Yes\n";
        }
    }
}