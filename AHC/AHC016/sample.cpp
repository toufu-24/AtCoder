#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

const int N = 15;
#define size  105// N*(N-1)/2

int main()
{
    int M;    //<=100
    double e; //<=0.4
    cin >> M >> e;

    cout << N << endl;
    for (int i = 0; i < M; i++)
    {
        bitset<size> G_sk;
        for (int k = 0; k < i; k++)
        {
            G_sk.set(k);
        }

        cout << G_sk << endl;
    }

    for (int i = 0; i < 100; i++)
    {
        bitset<size> H_k;
        cin >> H_k;
        int t_k = H_k.count();

        if (t_k >= M)
        {
            t_k = M - 1;
        }

        cout << t_k << endl;
    }
}