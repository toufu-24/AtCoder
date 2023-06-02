#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    int max = -1;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == '-' && S[i + 1] == 'o')
        {
            int count = 0;
            for (int j = i + 1; j < N; j++)
            {
                if (S[j] == 'o')
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            if (count > max)
            {
                max = count;
            }
        }
    }
    //逆からも
    for (int i = N - 1; i >= 0; i--)
    {
        if (S[i] == '-' && S[i - 1] == 'o')
        {
            int count = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                if (S[j] == 'o')
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            if (count > max)
            {
                max = count;
            }
        }
    }
    cout << max << endl;
}