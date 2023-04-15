#include <bits/stdc++.h>
using namespace std;

int main()
{
    int64_t N;
    cin >> N;
    vector<vector<char>> A(N, vector<char>(N));
    char max_num = '0';
    vector<pair<int, int>> num_place(1);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
            if (max_num < A[i][j])
            {
                max_num = A[i][j];
                while (num_place.size() != 1)
                {
                    num_place.pop_back();
                }
                num_place[0] = make_pair(i, j);
            }
            else if (max_num == A[i][j])
            {
                max_num = A[i][j];
                num_place.push_back(make_pair(i, j));
            }
        }
    }
    vector<int64_t> biggest;
    //最大値からスタート
    for (int i = 0; i < num_place.size(); i++)
    {
        // 8方向に全探索
        for (int j = 0; j < 8; j++)
        {
            string number;
            number += (A[num_place[i].first][num_place[i].second]);
            if (j == 0)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp = (num_place[i].second + k) / N;
                    number += A[num_place[i].first][num_place[i].second + k - tmp * N];
                }
            }
            else if (j == 1)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp1 = (num_place[i].first + k) / N;
                    int tmp2 = (num_place[i].second + k) / N;
                    number += (A[num_place[i].first + k - tmp1 * N][num_place[i].second + k - tmp2 * N]);
                }
            }
            else if (j == 2)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp = (num_place[i].first + k) / N;
                    number += (A[num_place[i].first + k - tmp * N][num_place[i].second]);
                }
            }
            else if (j == 3)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp1 = (num_place[i].first + k) / N;
                    int tmp2 = 0;
                    if (num_place[i].second - k < 0)
                    {
                        tmp2 = 1;
                    }
                    number += (A[num_place[i].first + k - tmp1 * N][num_place[i].second - k + tmp2 * N]);
                }
            }
            else if (j == 4)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp = 0;
                    if (num_place[i].second - k < 0)
                    {
                        tmp = 1;
                    }
                    number += (A[num_place[i].first][num_place[i].second - k + tmp * N]);
                }
            }
            else if (j == 5)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp1 = 0;
                    if (num_place[i].first - k < 0)
                    {
                        tmp1 = 1;
                    }
                    int tmp2 = 0;
                    if (num_place[i].second - k < 0)
                    {
                        tmp2 = 1;
                    }
                    number += (A[num_place[i].first - k + tmp1 * N][num_place[i].second - k + tmp2 * N]);
                }
            }
            else if (j == 6)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp = 0;
                    if (num_place[i].first - k < 0)
                    {
                        tmp = 1;
                    }
                    number += (A[num_place[i].first - k + tmp * N][num_place[i].second]);
                }
            }
            else if (j == 7)
            {
                for (int k = 1; k < N; k++)
                {
                    int tmp1 = 0;
                    if (num_place[i].first - k < 0)
                    {
                        tmp1 = 1;
                    }
                    int tmp2 = (num_place[i].second + k) / N;
                    number += (A[num_place[i].first - k + tmp1 * N][num_place[i].second + k - tmp2 * N]);
                }
            }
            biggest.push_back(stoll(number));
        }
    }
    sort(biggest.begin(), biggest.end());
    cout << biggest[biggest.size() - 1] << endl;
}