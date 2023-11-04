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
    int N;
    cin >> N;
    string S;
    cin >> S;
    for (int i = 0; i < N - 1; i++)
    {
        if (S[i] == 'a' && S[i + 1] == 'b')
        {
            cout << "Yes" << endl;
            return 0;
        }
        if (S[i] == 'b' && S[i + 1] == 'a')
        {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}