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
    vector<int> S(8);
    for (int i = 0; i < 8; i++)
        cin >> S[i];

    bool sorted = true;
    bool range = true;
    bool twentyfive = true;
    for (int i = 0; i < 7; i++)
    {
        if (S[i] > S[i + 1])
            sorted = false;
        if (100 > S[i] || S[i] > 675)
        {
            range = false;
        }
        if (S[i] % 25 != 0)
            twentyfive = false;
    }

    if (sorted && range && twentyfive)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}