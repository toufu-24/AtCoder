/*二次元平面上にN 個の点があります．i 個目の点の座標は (Xi,Yi) です． 「x 座標が a 以上 c 以下であり，y 座標が b 以上 d 以下であるような点は何個あるか？」 
という形式の質問が Q 個与えられるので，それぞれの質問に答えるプログラムを実装してください． なお，入力される値はすべて整数です．*/

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> X(1501, vector<int>(1501, 0));
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        int y;
        cin >> y;
        X[x][y]++;
    }
    // 累積和
    for (int i = 1; i <= 1500; i++)
    {
        for (int j = 2; j <= 1500; j++)
        {
            X[i][j] += X[i][j - 1];
        }
    }
    for (int j = 1; j <= 1500; j++)
    {
        for (int i = 2; i <= 1500; i++)
        {
            X[i][j] += X[i - 1][j];
        }
    }

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << X[c][d] - X[a - 1][d] - X[c][b - 1] + X[a - 1][b - 1] << endl;
    }
}