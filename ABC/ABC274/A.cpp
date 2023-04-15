#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    double A, B;
    cin >> A >> B;
    double number = B / A;
    number = number * pow(10, 3);
    number = round(number);
    number /= pow(10, 3);
    printf("%1.3lf", number);
}