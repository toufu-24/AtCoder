#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

// https://ei1333.github.io/luzhiled/snippets/math/binomial.html
template <typename T>
T binomial(int64_t N, int64_t K)
{
    if (K < 0 || N < K)
        return 0;
    T ret = 1;
    for (T i = 1; i <= K; ++i)
    {
        ret *= N--;
        ret /= i;
    }
    return ret;
}

int32_t main()
{
    int A, B, K;
    cin >> A >> B >> K;

    int total_length = A + B;
    string s;
    for (int i = 0; i < total_length; i++)
    {
        if (A == 0)
        {
            s += 'b';
            B--;
        }
        else if (B == 0)
        {
            s += 'a';
            A--;
        }
        else
        {
            // 残りの文字の通り数を考えると，二項係数で求められるはず
            int comb = binomial<int>(A + B - 1, A - 1);
            if (K <= comb)
            {
                s += 'a';
                A--;
            }
            else
            {
                s += 'b';
                B--;
                K -= comb;
            }
        }
    }

    cout << s << endl;
}