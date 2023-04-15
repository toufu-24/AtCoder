#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<double>> place(4, vector<double>(2));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> place[i][j];
        }
    }
    vector<vector<double>> vec(4, vector<double>(2));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            vec[i][j] = place[i + 1][j] - place[i][j];
        }
    }
    vec[3][0] = place[0][0] - place[3][0];
    vec[3][1] = place[0][1] - place[3][1];
    vector<double> length(4);
    for (int i = 0; i < 4; i++)
    {
        length[i] = abs(sqrt(pow(vec[i][0], 2) + pow(vec[i][1], 2)));
    }
    vector<double> angle(4);
    for (int i = 0; i < 3; i++)
    {
        angle[i] = acos((vec[i][0] * vec[i + 1][0] * -1 + vec[i][1] * vec[i + 1][1] * -1) / (length[i] * length[i + 1]));
    }

    angle[3] = acos((vec[3][0] * vec[0][0] * -1 + vec[3][1] * vec[0][1] * -1) / (length[3] * length[0]));

    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += angle[i];
    }

    if (sum > 2 * M_PI - 0.01 && sum < 2 * M_PI + 0.01)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}