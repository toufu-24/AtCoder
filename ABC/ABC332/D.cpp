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
    vector<int> perm_col(W);
    iota(all(perm_col), 0);

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
                // swapで何個動かすか
                int cnt1 = 0;
                vector<int> tmp_row = perm_row;
                for (int i = 0; i < H; i++)
                {
                    if (i != tmp_row[i])
                    {
                        cnt1++;
                        swap(tmp_row[i], tmp_row[tmp_row[i]]);
                    }
                }
                int cnt2 = 0;
                vector<int> tmp_col = perm_col;
                for (int j = 0; j < W; j++)
                {
                    if (j != tmp_col[j])
                    {
                        cnt2++;
                        swap(tmp_col[j], tmp_col[tmp_col[j]]);
                    }
                }
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
