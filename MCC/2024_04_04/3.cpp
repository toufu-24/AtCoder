#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, K;
    cin >> N >> K;
    string K_str = to_string(K);
    REVERSE(K_str);
    if (stoll(K_str) < K)
    {
        cout << 0 << endl;
        return 0;
    }
    set<int> ans;
    if (K <= N)
        ans.insert(K);
    if (stoll(K_str) <= N)
        ans.insert(stoll(K_str));
    queue<int> q;
    q.push(K);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        string x_str = to_string(x);
        x_str += "0";
        if (stoll(x_str) <= N)
        {
            if (ans.contains(stoll(x_str)))
                continue;
            ans.insert(stoll(x_str));
            q.push(stoll(x_str));
        }
        x_str.pop_back();
        REVERSE(x_str);
        x_str += "0";
        if (stoll(x_str) <= N)
        {
            if (ans.contains(stoll(x_str)))
                continue;
            ans.insert(stoll(x_str));
            q.push(stoll(x_str));
        }
    }
    cout << ans.size() << endl;
}
