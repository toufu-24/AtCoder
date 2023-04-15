#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int Q;
    cin >> Q;
    vector<int> L(Q);
    vector<int> R(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> L[i] >> R[i];
    }
    vector<int> hit(N, 0);
    int hit_cnt = 0;
    vector<int> miss(N, 0);
    int miss_cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (A[i] == 1)
        {
            hit_cnt++;
        }
        else
        {
            miss_cnt++;
        }
        hit[i] = hit_cnt;
        miss[i] = miss_cnt;
    }
    for (int i = 0; i < Q; i++)
    {
        int hit_num = hit[R[i] - 1] - hit[L[i] - 2];
        int miss_num = miss[R[i] - 1] - miss[L[i] - 2];
        if (hit_num > miss_num)
        {
            cout << "win";
        }
        else if (hit_num < miss_num)
        {
            cout << "lose";
        }
        else
        {
            cout << "draw";
        }
        cout << endl;
    }
}