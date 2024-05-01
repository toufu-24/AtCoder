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

int ans = 0;
int K;

int32_t main()
{
    cin >> K;
    if (K < 10)
    {
        cout << K << endl;
        return 0;
    }
    int cnt = 0;
    queue<string> q;
    for (int i = 1; i <= 9; i++)
    {
        q.push(to_string(i));
    }
    while (cnt < K)
    {
        string now = q.front();
        q.pop();
        cnt++;
        if (cnt == K)
        {
            cout << now << endl;
            return 0;
        }
        int last = now.back() - '0';
        if (last == 0)
        {
            q.push(now + '0');
            q.push(now + '1');
        }
        else if (last==9)
        {
            q.push(now + '8');
            q.push(now + '9');
        }
        else
        {
            q.push(now + to_string(last - 1));
            q.push(now + to_string(last));
            q.push(now + to_string(last + 1));
        }   
    }
}
