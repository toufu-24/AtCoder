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
    vector<pair<int, string>> v(N);
    int min = -1, index = -1;

    for (int i = 0; i < N; i++)
    {
        string S;
        int P;
        cin >> S >> P;
        v[i] = make_pair(P, S);
        if (min == -1 || min > P)
        {
            min = P;
            index = i;
        }
    }

    for (int i = index; i < N; i++)
    {
        cout << v[i].second << endl;
    }
    for (int i = 0; i < index; i++)
    {
        cout << v[i].second << endl;
    }
}