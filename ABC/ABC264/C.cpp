#include <bits/stdc++.h>
using namespace std;

bool equal_judge(vector<vector<int>> A, vector<vector<int>> B)
{
    if (A.size() != B.size() || A.at(0).size() != B.at(0).size())
        return false;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.at(0).size(); j++)
        {
            if (A[i][j] != B[i][j])
                return false;
        }
    }
    return true;
}

vector<pair<int, int>> same_value(vector<vector<int>> A, vector<vector<int>> B)
{
}

int for_num(int n, int r)
{
    if (n == 0 || n == r)
        return 1;
    return for_num(n - 1, r - 1) + for_num(n - 1, r);
}

int main()
{
    int H1, W1;
    cin >> H1 >> W1;
    vector<vector<int>> A(H1, vector<int>(W1));
    for (int i = 0; i < H1; i++)
    {
        for (int j = 0; j < W1; j++)
        {
            cin >> A[i][j];
        }
    }
    int H2, W2;
    cin >> H2 >> W2;
    vector<vector<int>> B(H2, vector<int>(W2));
    for (int i = 0; i < H2; i++)
    {
        for (int j = 0; j < W2; j++)
        {
            cin >> B[i][j];
        }
    }
    const int wide = W1 - W2;
    const int height = H1 - H2;
    int w_num = for_num(W1, wide);
    int h_num = for_num(H1, height);

    int w_line[w_num][wide];
    for (int i = 0; i < w_num; i++)
    {
        for (int j = 0; j < wide; j++)
        {
            w_line[i][j] = rand() % wide;
        }
    }
    int h_line[h_num][height];
    for (int i = 0; i < h_num; i++)
    {
        for (int j = 0; j < height; j++)
        {
            h_line[i][j] = rand() % height;
        }
    }
    vector<vector<int>> clone_A(H1, vector<int>(W1));

    if (w_num != 0 && h_num != 0)
    {
        for (int i = 0; i < w_num; i++)
        {
            for (int j = 0; j < h_num; j++)
            {
                for (int k = 0; k < H1; k++)
                {
                    for (int l = 0; l < W1; l++)
                    {
                        if (k == w_line[i][j])
                            clone_A[k][l] = A[k][l];
                    }
                }
                if (equal_judge(clone_A, B))
                    cout << "Yes";
            }
        }
    }
    cout << "No";
    /*if (equal_judge(A, B))
    {
        cout << "Yes" << endl;
        return 0;
    }
    for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                {
}
}
* /*/
}