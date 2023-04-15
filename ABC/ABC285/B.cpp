#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    string S;
    cin >> N >> S;
    for (int i = 1; i < N; i++)
    {
        int l = 0;
        int j;
        for (j = 0; j < N - i; j++)
        {
            if (S[j] == S[j + i])
            {
                break;
            }
        }
        cout << j << endl;
    }
}