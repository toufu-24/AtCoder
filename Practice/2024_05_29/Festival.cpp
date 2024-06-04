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
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    for (int i = 0; i < M; i++)
    {
        cin >> A[i];
        A[i]--;
    }

    vector<int> sum(N + 1, 0);
    int a_idx = 0;
    for (int i = 0; i < N; i++)
    {
        if (a_idx < M && A[a_idx] == i)
        {
            sum[i + 1] = sum[i] + 1;
            a_idx++;
        }
        else
        {
            sum[i + 1] = sum[i];
        }
    }

    for (int i = 0; i < N; i++)
    {
        int ok = N, ng = i;
        while (ok - ng > 1)
        {
            int mid = (ok + ng) / 2;
            if (sum[mid] - sum[i] >= 1)
            {
                ok = mid;
            }
            else
            {
                ng = mid;
            }
        }
        cout << ok - i - 1 << endl;
    }
}
