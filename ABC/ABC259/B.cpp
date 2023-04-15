#include <bits/stdc++.h>
using namespace std;

int main()
{
    double a, b, d;
    cin >> a >> b >> d;
    double argument = d * M_PI / 180;
    complex<double> place(a, b);
    complex<double> i(0, 1);
    place *= cos(argument) + i * sin(argument);
    printf("%.10lf %.10lf", place.real(), place.imag());
}