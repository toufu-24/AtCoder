#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    vector<int> b(M);
    for (int i = 0; i < M; i++)
    {
        cin >> b[i];
    }
    int now = 0;
    int idx = 0;
    for (int i = 0; i < N; i++)
    {
        if (a[i] == b[0])
        {
            idx = i;
            break;
        }
        else if (a[-i + N] == b[0])
        {
            idx = -i + N;
            break;
        }
    }
}