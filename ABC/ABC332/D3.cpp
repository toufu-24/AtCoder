#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<vector<int>> A;

// int selection_sort(vector<int> v,vector<int> A_v)
// {
//     int ret = 0;
//     int N = v.size();
//     for (int i = 0; i < N; i++)
//     {
//         int minj = i;
//         for (int j = i; j < N; j++)
//         {
//             if (v[j] == A_v[i])
//             {
//                 minj = j;
//                 break;
//             }
//         }
//         if (minj != i)
//         {
//             swap(v[i], v[minj]);
//             ret++;
//         }
//     }
//     return ret;
// }

int bubble_sort(vector<int> v, const vector<int> A_v)
{
    int ret = 0;
    int N = v.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (v[j] == A_v[i])
            {
                for (int k = j; k > i; k--)
                {
                    swap(v[k], v[k - 1]);
                    ret++;
                }
                break;
            }
        }
    }
    return ret;
}

int main()
{
    int H, W;
    cin >> H >> W;
    A.resize(H, vector(W, 0));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> A[i][j];
        }
    }

    vector B_(H, vector(W, 0));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> B_[i][j];
        }
    }
    const vector B = B_;

    vector<int> perm_row(H);
    iota(all(perm_row), 0);
    vector<int> normal_row(H);
    iota(all(normal_row), 0);
    vector<int> perm_col(W);
    iota(all(perm_col), 0);
    vector<int> normal_col(W);
    iota(all(normal_col), 0);

    int ans = 1e9;
    do
    {
        do
        {
            vector C(H, vector(W, 0));
            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    C[i][j] = A[perm_row[i]][perm_col[j]];
                }
            }
            if (C == B)
            {
                int cnt1 = 0;
                int cnt2 = 0;
                cnt1 = bubble_sort(perm_row, normal_row);
                cnt2 = bubble_sort(perm_col, normal_col);
                cerr << cnt1 << " " << cnt2 << '\n';
                int cnt = cnt1 + cnt2;
                ans = min(ans, cnt);
            }
        } while (next_permutation(all(perm_col)));
    } while (next_permutation(all(perm_row)));

    if (ans != 1e9)
    {
        cout << ans << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}
