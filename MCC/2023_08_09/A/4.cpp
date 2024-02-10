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
    int A, B, W;
    cin >> A >> B >> W;
    W *= 1000;
    if (A > W)
    {
        cout << "UNSATISFIABLE" << endl;
        return 0;
    }

    int minimum = 1e9, maximum = 0;
    for (int i = 1; i <= 1e6; i++)
    {
        // i個選ぶ時があり得るか
        if (A * i <= W && W <= B * i)
        {
            minimum = min(minimum, i);
            maximum = max(maximum, i);
        }
    }
    if (minimum == 1e9)
    {
        cout << "UNSATISFIABLE" << endl;
    }
    else
    {
        cout << minimum << " " << maximum << endl;
    }
}