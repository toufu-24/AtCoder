#include <bits/stdc++.h>
using namespace std;

int main()
{
    int64_t N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    int max_num = 0;
    pair<int, int> num_place;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
            //! 最大が複数ある場合の処理無し
            if (max_num < A[i][j])
            {
                max_num = A[i][j];
                num_place = make_pair(i, j);
            }
        }
    }
    string number = to_string(max_num);
    for (int i = 0; i < N - 1; i++)
    {
        //右から時計回り
        pair<int, int> tmp_place;
        int biggest_num;
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
            {
                if (num_place.second == N - 1)
                {
                    biggest_num = A[num_place.first][0];
                    tmp_place = make_pair(num_place.first, 0);
                }
                else
                {
                    biggest_num = A[num_place.first][num_place.second + 1];
                    tmp_place = make_pair(num_place.first, num_place.second + 1);
                }
            }
            else if (j == 1)
            {
                if (num_place.first == N - 1 && num_place.second == N - 1)
                {
                    if (A[0][0] > biggest_num)
                    {
                        biggest_num = A[0][0];
                        tmp_place = make_pair(0, 0);
                    }
                }
                else if (num_place.first == N - 1)
                {
                    if (A[0][num_place.second + 1] > biggest_num)
                    {
                        biggest_num = A[0][num_place.second + 1];
                        tmp_place = make_pair(0, num_place.second + 1);
                    }
                }
                else if (num_place.second == N - 1)
                {
                    if (A[num_place.first + 1][0] > biggest_num)
                    {
                        biggest_num = A[num_place.first + 1][0];
                        tmp_place = make_pair(num_place.first + 1, 0);
                    }
                }
                else
                {
                    if (A[num_place.first + 1][num_place.second + 1] > biggest_num)
                    {
                        biggest_num = A[num_place.first + 1][num_place.second + 1];
                        tmp_place = make_pair(num_place.first + 1, num_place.second + 1);
                    }
                }
            }
            else if (j == 2)
            {
                if (num_place.second == N - 1)
                {
                    if (A[num_place.first][0] > biggest_num)
                    {
                        biggest_num = A[num_place.first][0];
                        tmp_place = make_pair(num_place.first, 0);
                    }
                }
                else if (A[num_place.first + 1][num_place.second] > biggest_num)
                {
                    if (A[num_place.first + 1][num_place.second] > biggest_num)
                    {
                        biggest_num = A[num_place.first + 1][num_place.second];
                        tmp_place = make_pair(num_place.first + 1, num_place.second);
                    }
                }
            }
            else if (j == 3)
            {
                if (num_place.first == N - 1 && num_place.second == 0)
                {
                    if (A[0][N - 1] > biggest_num)
                    {
                        biggest_num = A[0][N - 1];
                        tmp_place = make_pair(0, N - 1);
                    }
                }
                else if (num_place.first == N - 1)
                {
                    if (A[0][num_place.second - 1] > biggest_num)
                    {
                        biggest_num = A[0][num_place.second - 1];
                        tmp_place = make_pair(0, num_place.second - 1);
                    }
                }
                else if (num_place.second == 0)
                {
                    if (A[num_place.first + 1][N - 1] > biggest_num)
                    {
                        biggest_num = A[num_place.first + 1][N - 1];
                        tmp_place = make_pair(num_place.first + 1, N - 1);
                    }
                }
                else
                {
                    if (A[num_place.first + 1][num_place.second - 1] > biggest_num)
                    {
                        biggest_num = A[num_place.first + 1][num_place.second - 1];
                        tmp_place = make_pair(num_place.first + 1, num_place.second - 1);
                    }
                }
            }
            else if (j == 4)
            {
                if (num_place.second == 0)
                {
                    if (A[num_place.first + 1][N - 1] > biggest_num)
                    {
                        biggest_num = A[num_place.first][N - 1];
                        tmp_place = make_pair(num_place.first, N - 1);
                    }
                }
                else
                {
                    if (A[num_place.first][num_place.second - 1] > biggest_num)
                    {
                        biggest_num = A[num_place.first][num_place.second - 1];
                        tmp_place = make_pair(num_place.first, num_place.second - 1);
                    }
                }
            }
            else if (j == 5)
            {
                /* code */
            }
            else if (j == 6)
            {
                /* code */
            }
            else if (j == 7)
            {
                /* code */
            }
        }
        num_place = tmp_place;
    }
}