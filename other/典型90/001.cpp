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
    int N, L;
    cin >> N >> L;
    int K;
    cin >> K;
    vector<int> sum(N);
    for (int i = 0; i < N; i++)
    {
        cin >> sum[i];
    }
    vector<int> A(N);
    A[0] = sum[0];
    for (int i = 1; i < N; i++)
    {
        A[i] = sum[i] - sum[i - 1];
    }
    A.push_back(L - sum[N - 1]);

    int ok = 1, ng = L + 1;
    while (abs(ng - ok) > 1)
    {
        // 全てのK+1個をmid以上にできるか
        int mid = (ok + ng) / 2;
        int cnt = 1;
        int now_length = 0;
        for (int i = 0; i < A.size(); i++)
        {
            if (now_length < mid)
            {
                now_length += A[i];
            }
            else
            {
                if (cnt < K + 1)
                {
                    now_length = A[i];
                    cnt++;
                }
                else
                {
                    now_length += A[i];
                }
            }
        }
        if (cnt >= K + 1 && now_length >= mid)
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    cout << ok << endl;
}
