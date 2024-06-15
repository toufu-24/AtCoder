#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < N; j++)
        {
            A[i][j] = tmp[j] - '0';
        }
    }

    modint::set_mod(N);
    vector<int> ans;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // i, j からスタート
            for (int d = 0; d < 8; d++)
            {
                string num = to_string(A[i][j]);
                modint x = i, y = j;
                for (int k = 0; k < N - 1; k++)
                {
                    x += dx[d];
                    y += dy[d];
                    num += to_string(A[x.val()][y.val()]);
                }
                ans.push_back(stoll(num));
            }
        }
    }
    cout << *max_element(all(ans)) << endl;
}
