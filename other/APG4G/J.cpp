#include <bits/stdc++.h>
using namespace std;

int main()
{
    int x, a, b;
    int count;
    cin >> x >> a >> b;

    // 1.の出力
    cout << ++x << endl;

    // ここにプログラムを追記
    x *= (a + b);
    cout << x << endl;
    x *= x;
    cout << x << endl;
    cout << --x << endl;
}
