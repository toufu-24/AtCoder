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
    int N;
    cin >> N;
    string S;
    cin >> S;
    int taka = 0, aoki = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'T')
            taka++;
        else
            aoki++;
    }
    if (taka < aoki)
        cout << "A" << endl;
    else if (taka == aoki)
    {
        if (S[N - 1] == 'T')
            cout << "A" << endl;
        else
            cout << "T" << endl;
    }
    else
        cout << "T" << endl;
}