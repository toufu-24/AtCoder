#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    int two_cnt = 0;
    for (int q = 0; q < Q; q++)
    {
        int t, a, b;
        cin >> t >> a >> b;
        switch (t)
        {
        case 1:
            if (two_cnt % 2 == 0)
            {
                swap(S[a - 1], S[b - 1]);
            }
            else
            {
                if (a <= N)
                {
                    a += N;
                }
                else
                {
                    a -= N;
                }
                if (b <= N)
                {
                    b += N;
                }
                else
                {
                    b -= N;
                }
                swap(S[a - 1], S[b - 1]);
            }
            break;
        case 2:
            two_cnt++;
            break;
        }
    }
    if (two_cnt % 2 == 1)
    {
        for (int i = 0; i < N; i++)
        {
            swap(S[i], S[N + i]);
        }
    }
    cout << S;
}