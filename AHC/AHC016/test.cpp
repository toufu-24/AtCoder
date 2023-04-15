#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

const int N = 7;

int main()
{
    int M;
    double e;
    cin >> M >> e;

    vector<string> str(M);
    cout << N << endl;
    cout << flush;
    for (int i = 1; i < M + 1; i++)
    {
        cout << static_cast<bitset<7>>(i) << endl;
        cout << flush;
    }

    for (int i = 0; i < 100; i++)
    {
        string k;
        cin >> k;
        int t_k = 0;
        for (int j = 0; j < k.size(); j++)
        {
            if (k[j] == '1')
            {
                t_k += pow(2, k.size() - j - 1);
            }
        }
        cout << t_k << endl;
        cout << flush;
    }
}