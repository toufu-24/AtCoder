#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ull uint64_t

int main()
{
    int N, K, Q;
    cin >> N >> K >> Q;
    vector<int> A(N, 0);
    int F_A = 0;
    vector<bool> F(N, false);
    int min_F = 0;
    int min_F_index = 0;
    int max_notF = 0;
    int max_notF_index = 0;
    int num_cnt = 0;
    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        if (F[x])
        {
            if (y >= min_F)
            {
                F_A -= min_F;
                F_A += y;
                vector<int> tmp = A;
                sort(tmp);
                reverse(tmp);
                int second_min = tmp[K - 2];
                if (second_min < y)
                {
                    for (int k = 0; k < N; k++)
                    {
                        if (A[k] == second_min)
                        {
                            min_F_index = k;
                            break;
                        }
                    }
                }
                else
                {
                    min_F_index = x;
                }
            }
            else
            {
                if (max_notF < y)
                {
                    F_A -= A[x];
                    F_A += y;
                }
                else
                {
                    F_A -= A[x];
                    F_A += max_notF;
                    F[max_notF_index] = true;
                    F[x] = false;
                    A[x] = y;
                    continue;
                }
            }
        }
        else if (y > min_F)
        {
            num_cnt++;
            if (num_cnt == K)
            {
                int tmp = INT32_MAX;
                for (int w = 0; w < N; w++)
                {
                    if (F[w])
                    {
                        if (A[w] < tmp)
                        {
                            tmp = A[w];
                        }
                    }
                }
                min_F = tmp;
            }
            vector<int> tmp = A;
            sort(tmp);
            reverse(tmp);
            int second_min = tmp[K - 2];
            if (second_min < y)
            {
                for (int k = 0; k < N; k++)
                {
                    if (A[k] == second_min)
                    {
                        min_F_index = k;
                        break;
                    }
                }
            }
            else
            {
                min_F_index = x;
            }
            F_A -= min_F;
            F_A += y;
            F[x] = true;
        }
        A[x] = y;
        cout << F_A << endl;
    }
}