#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll
signed main()
{
    int N, M;
    cin >> N >> M;
    vector<int> L(N);
    for (int i = 0; i < N; i++)
    {
        cin >> L[i];
    }
    int left = *max_element(all(L));
    int right = 1e18;
    while (right - left > 1)
    {
        int mid = (left + right) / 2;
        int now_lines = 1;
        int now_index = 0;
        while (true)
        {
            int now_length = 0;
            bool break_flag = false;
            while (now_length + L[now_index] + ((now_length == 0) ? 0 : 1) <= mid)
            {
                now_length += L[now_index++] + ((now_length == 0) ? 0 : 1);
                if (now_index == N)
                {
                    break_flag = true;
                    break;
                }
            }
            if (break_flag)
            {
                break;
            }
            now_lines++;
            if (now_lines > M)
            {
                break;
            }
        }
        if (now_lines <= M)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    cout << right;
}