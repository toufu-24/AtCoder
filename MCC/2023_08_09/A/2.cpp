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
    int A, B;
    cin >> A >> B;
    string S;
    cin >> S;
    for (int i = 0; i < A + B + 1; i++)
    {
        if (i == A)
        {
            if (S[i] != '-')
            {
                cout << "No" << endl;
                return 0;
            }
        }
        else
        {
            if (S[i] < '0' || S[i] > '9')
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
}