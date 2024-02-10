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

int main()
{
    int N, A, B;
    cin >> N >> A >> B;
    vector ans(A * N, vector<char>(B * N, '0'));
    char c[2] = {'.', '#'};
    int idx = 0;
    for (int i = 0; i < A * N; i += A)
    {
        for (int j = 0; j < B * N; j += B)
        {
            for (int a = 0; a < A; a++)
            {
                for (int b = 0; b < B; b++)
                {
                    ans[i + a][j + b] = c[idx];
                }
            }
            idx = 1 - idx;
        }
        if (N % 2 == 0)
            idx = 1 - idx;
    }
    for (int i = 0; i < A * N; i++)
    {
        for (int j = 0; j < B * N; j++)
        {
            cout << ans[i][j];
        }
        cout << endl;
    }
}