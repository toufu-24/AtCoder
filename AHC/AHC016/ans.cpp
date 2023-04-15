#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

const int N = 21;
#define size 210 // N*(N-1)/2
#define parallel 2
#define one_block 100

int main()
{
    srand(time(NULL));
    int M;    //<=100
    double e; //<=0.4
    cin >> M >> e;

    cout << N << endl;
    for (int i = 0; i < M; i++)
    {
        bitset<size> G_sk;
        for (int j = 0; j < parallel; j++)
        {
            for (int k = 0; k < i; k++)
            {
                G_sk.set(j * one_block + k);
            }
        }
        cout << G_sk << endl;
    }

    for (int i = 0; i < 100; i++)
    {
        bitset<size> H_k;
        cin >> H_k;
        int sum = H_k.count();
        int t_k = 0;
        double average = (double)sum / (double)parallel;
        t_k = round(average);

        if (t_k >= M)
        {
            t_k = M - 1;
        }

        cout << t_k << endl;
    }
}