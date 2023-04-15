#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    cin >> N;

    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    for (int i = 0; i < N; i++)
    {
        cout << S[N - i - 1] << endl;
    }
}