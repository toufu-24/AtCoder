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

int32_t main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    map<int, int> a_mp;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        a_mp[a[i]]++;
    }
    SORT(a);
    set<int> mex;
    for (int i = 1; i < 5e5; i++)
    {
        if (!a_mp.contains(i))
        {
            mex.insert(i);
        }
    }

    deque<int> dq;
    for (int i = 0; i < N; i++)
    {
        dq.push_back(a[i]);
    }

    // 2つ消費したらmexを消せるよ
    int now = 0;
    while (true)
    {
        if (dq.size() == 0)
        {
            break;
        }
        int x = dq.front();
        if (x == now + 1)
        {
            dq.pop_front();
            now++;
        }
        else if (x > now + 1)
        {
            dq.push_front(now + 1);
            dq.pop_back();
            dq.pop_back();
        }
        else
        {
            if (dq.size() == 1)
            {
                break;
            }
            int cnt = 0;
            while (dq.size() > 1 && dq[0] < now + 1 && dq[1] < now + 1)
            {
                cnt++;
                dq.pop_front();
                dq.pop_front();
            }
            vector<int> add(cnt);
            for (int i = 0; i < cnt; i++)
            {
                add[i] = *mex.begin();
                mex.erase(mex.begin());
            }
            REVERSE(add);
            for (int i = 0; i < cnt; i++)
            {
                dq.push_front(add[i]);
            }
        }
    }
    cout << now << endl;
}
