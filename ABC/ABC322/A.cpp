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
    for (int i = 0; i < N; i++)
    {
        string T = S.substr(i, 3);
        cerr << T << endl;
        if (T == "ABC")
        {
            cout << i + 1;
            return 0;
        }
    }
    cout << -1;
}