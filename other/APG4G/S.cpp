#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, S;
    cin >> N >> S;
    int count = 0;
    vector<int> A(N), P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A.at(i);
    }
    for (int i = 0; i < N; i++)
    {
        cin >> P.at(i);
    }

    // リンゴ・パイナップルをそれぞれ1つずつ購入するとき合計S円になるような買い方が何通りあるか
    // ここにプログラムを追記

    for (int x : A)
    {
        for (int y : P)
        {
            if (x + y == S)
            {
                count++;
            }
        }
    }

    cout << count << endl;
}
