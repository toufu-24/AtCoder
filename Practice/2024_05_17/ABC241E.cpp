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

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    modint::set_mod(N);
    modint X = 0;
    map<int, int> idx;
    vector<int> sum;
    sum.push_back(0);
    int candy = 0;
    for (int i = 0; i < K; i++)
    {
        if (!idx.contains(X.val()))
        {
            idx[X.val()] = i;
            candy += A[X.val()];
            X += A[X.val()];
            sum.push_back(candy);
        }
        else
        {
            int prev = idx[X.val()];
            int loop = i - prev;
            int loop_candy = candy - sum[prev];
            int n = (K - i) / loop;
            X += n * loop_candy;
            i += n * loop;
            candy += n * loop_candy;
            for (int j = 0; j < K - i; j++)
            {
                candy += A[X.val()];
                X += A[X.val()];
            }
            goto end;
        }
    }
end:
    cout << candy << endl;
}
