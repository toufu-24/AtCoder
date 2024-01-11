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
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    int have_logo = 0;
    int have_white = M;
    int used_white = 0;
    int used_logo = 0;
    for (int i = 0; i < N; i++)
    {
        switch (S[i])
        {
        case '0':
            used_logo = 0;
            used_white = 0;
            break;
        case '1':
            if (used_white == have_white)
            {
                used_logo++;
                if (used_logo > have_logo)
                {
                    have_logo++;
                }
            }
            else
            {
                used_white++;
            }
            break;
        case '2':
            used_logo++;
            if (used_logo > have_logo)
            {
                have_logo++;
            }
            break;
        default:
            break;
        }
    }
    cout << have_logo << endl;
}