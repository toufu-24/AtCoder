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

ll cnt = 0;
ll K;
string ans = "";
set<string> st;
void dfs(int keta, int now_hukasa, int now_disit, string now_num)
{
    if (now_num == "0")
    {
        return;
    }
    if (keta == now_hukasa)
    {
        if (st.count(now_num))
        {
            return;
        }
        st.insert(now_num);
        cnt++;
        if (cnt == K)
        {
            cout << now_num << endl;
            exit(0);
        }
        return;
    }
    if (now_disit == 0)
    {
        return;
    }
    for (int i = 0; i < now_disit; i++)
    {
        dfs(keta, now_hukasa + 1, i, now_num + char(i + '0'));
    }
}

int main()
{
    cin >> K;
    for (int keta = 1; true; keta++)
    {
        for (int i = 1; i <= 9; i++)
        {
            dfs(keta, 1, i, to_string(i));
        }
    }
}