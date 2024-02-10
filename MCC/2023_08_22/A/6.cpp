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
    int x0, y0;
    cin >> x0 >> y0;
    int xN2, yN2;
    cin >> xN2 >> yN2;

    // 図形の中央を中心に2 * Pi / NだけP0から反時計回りに回転させたやつが答え
    complex<double> p0(x0, y0);
    complex<double> pN2(xN2, yN2);
    complex<double> center = (p0 + pN2) / 2.0;
    double theta = 2 * M_PI / N;
    complex<double> i(0, 1);
    complex<double> ans = (p0 - center) * (cos(theta) + i * sin(theta)) + center;
    cout << fixed << setprecision(10) << ans.real() << " " << ans.imag();
}