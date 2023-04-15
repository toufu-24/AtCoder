#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    string H, M;
    cin >> H >> M;
    int H2 = stoi(H);
    int M2 = stoi(M);
    while (true)
    {
        H = to_string(H2);
        M = to_string(M2);
        if (H.size() == 1)
        {
            char tmp = H[0];
            H = '0';
            H += tmp;
        }
        if (M.size() == 1)
        {
            char tmp = M[0];
            M = '0';
            M += tmp;
        }

        char tmp = H[1];
        H[1] = M[0];
        M[0] = tmp;
        int int_h = stoi(H);
        int int_m = stoi(M);

        if (int_h < 24 && 0 <= int_h)
        {
            if (int_m < 60 && 0 <= int_m)
            {
                cout << H2 << " " << M2;
                return 0;
            }
        }

        M2++;
        if (M2 == 60)
        {
            H2++;
            M2 = 0;
        }
        if (H2 == 24)
        {
            H2 = 0;
        }
    }
}