#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, A;
    cin >> N >> A;

    // ここにプログラムを追記
    int B[7];
    string P[7];
    for (int i = 0; i < N; i++)
    {
        cin >> P[i] >> B[i];
    }

    for (int i = 0; i < N; i++)
    {
        if (P[i] == "+")
            A += B[i];
        else if (P[i] == "-")
            A -= B[i];
        else if (P[i] == "*")
            A *= B[i];
        else if (P[i] == "/" && B[i] != 0)
            A /= B[i];
        else if (P[i] == "/" && B[i] == 0)
        {
            cout << "error" << endl;
            break;
        }

        cout << i + 1 << ":" << A << endl;
    }
}
