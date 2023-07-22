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
    bool a = false, b = false, c = false;
    for (int i = 0; i < N; i++)
    {
        switch (S[i])
        {
        case 'A':
            a = true;
            break;
        case 'B':
            b = true;
            break;
        case 'C':
            c = true;
            break;
        default:
            break;
        }
        if (a && b && c)
        {
            cout << i + 1;
            return 0;
        }
    }
    cout << N;
}