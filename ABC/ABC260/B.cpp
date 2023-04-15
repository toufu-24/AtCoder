#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, X, Y, Z;
    cin >> N >> X >> Y >> Z;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A.at(i);
    }
    vector<int> B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> B.at(i);
    }

    vector<pair<int, int>> math(N);
    vector<pair<int, int>> eng(N);
    vector<pair<int, int>> sum(N);
    for (int i = 0; i < N; i++)
    {
        math.at(i).first = -1 * A.at(i);
        math.at(i).second = i;
        eng.at(i).first = -1 * B.at(i);
        eng.at(i).second = i;
        sum.at(i).first = -1 * A.at(i) - 1 * B.at(i);
        sum.at(i).second = i;
    }
    sort(math.begin(), math.end());
    sort(eng.begin(), eng.end());
    sort(sum.begin(), sum.end());

    for (int i = 0; i < N; i++)
    {
        math.at(i).first *= -1;
        eng.at(i).first *= -1;
        sum.at(i).first *= -1;
    }

    vector<int> pass_num(X + Y + Z, -1);
    for (int i = 0; i < X; i++)
    {
        pass_num.at(i) = math.at(i).second;
    }
    int a;
    for (int i = 0, a = 0; i < Y; i++)
    {

        for (int j = 0; j < X; j++)
        {
            if (eng.at(a).second == pass_num.at(j))
            {

                a++;
                j = -1;
            }
        }
        pass_num.at(i + X) = eng.at(a).second;
        a++;
    }
    // sum
    for (int i = 0, a = 0; i < Z; i++)
    {
        for (int j = 0; j < X + Y; j++)
        {
            if (sum.at(a).second == pass_num.at(j))
            {
                a++;
                j = -1;
            }
        }
        pass_num.at(i + X + Y) = sum.at(a).second;
        a++;
    }
    sort(pass_num.begin(), pass_num.end());

    for (int i = 0; i < X + Y + Z; i++)
    {
        cout << pass_num.at(i) + 1 << endl;
    }
}