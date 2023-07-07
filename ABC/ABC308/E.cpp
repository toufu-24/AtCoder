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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    string S;
    cin >> S;

    vector<int> M_indexes;
    vector<int> E_indexes;
    vector<int> X_indexes;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'M')
        {
            M_indexes.push_back(i);
        }
        else if (S[i] == 'E')
        {
            E_indexes.push_back(i);
        }
        else if (S[i] == 'X')
        {
            X_indexes.push_back(i);
        }
    }

    ll sum = 0;
    // O(N^3) だと間に合わない～
    int M_size = M_indexes.size();
    int E_size = E_indexes.size();
    int X_size = X_indexes.size();
    for (int i = 0; i < M_size; i++)
    {
        int m = M_indexes[i];
        for (int j = 0; j < E_size; j++)
        {
            int e = E_indexes[j];
            if (e <= m)
            {
                continue;
            }
            for (int k = 0; k < X_size; k++)
            {
                int x = X_indexes[k];
                if (x <= e)
                {
                    continue;
                }
                if (A[m] != 0 && A[e] != 0 && A[x] != 0)
                {
                    sum += 0;
                }
                else if (A[m] != 1 && A[e] != 1 && A[x] != 1)
                {
                    sum += 1;
                }
                else if (A[m] != 2 && A[e] != 2 && A[x] != 2)
                {
                    sum += 2;
                }
                else
                {
                    sum += 3;
                }
            }
        }
    }

    cout << sum << endl;
}