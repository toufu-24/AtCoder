#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
// #define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double
string X;

int main()
{
    cin >> X;
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    sort(all(S),
         [](const string &a, const string &b)
         {
             for (int i = 0; i < min(a.size(), b.size()); i++)
             {
                 if (a[i] != b[i])
                 {
                     int a_i = 0;
                     for (auto c : X)
                     {
                         if (c == a[i])
                         {
                             break;
                         }
                         a_i++;
                     }
                     int b_i = 0;
                     for (auto c : X)
                     {
                         if (c == b[i])
                         {
                             break;
                         }
                         b_i++;
                     }
                     return a_i < b_i;
                 }
             }
             return a.size() < b.size();
         });
    for (int i = 0; i < N; i++)
    {
        cout << S[i] << endl;
    }
}