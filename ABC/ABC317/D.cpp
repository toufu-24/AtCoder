#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<tuple<double, int, int>> elect;
    // vector<int>;
    int now_giseki = 0;
    int giseki_sum = 0;
    for (int i = 0; i < N; i++)
    {
        int X, Y, Z;
        cin >> X >> Y >> Z;
        giseki_sum += Z;
        if (X > Y)
        {
            now_giseki += Z;
        }
        else
        {
            int need = ceil(double(Y) / 2) - X / 2;
            elect.push_back({Z / double(need), need, Z});
        }
    }
    sort(elect);
    int need = ceil(double(giseki_sum) / 2) - now_giseki;
    cout << need << endl;
}