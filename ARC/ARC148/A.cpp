#include <bits/stdc++.h>
using namespace std;

int prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int min = 2;
    sort(A.begin(), A.end());

    for (int i = 2; 1; i += 2)
    {
        bool prime_flag = true;
        for (int j = 0; j < 25; j++)
        {
            if (i <= prime[j])
            {
                break;
            }
            else if (i % prime[j] == 0)
            {
                prime_flag = false;
                break;
            }
        }

        if (prime_flag)
        {
            bool flag = true;
            vector<int> tmp(N);
            tmp[0] = A[0] % i;
            for (int j = 1; j < N; j++)
            {
                tmp[j] = A[j] % i;
                if (tmp[j] != tmp[j - 1])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                min = 1;
                break;
            }
        }
        if (i == 2)
        {
            i--;
        }
        if ((double)(double(clock()) / double(CLOCKS_PER_SEC)) > 1.9)
        {
            break;
        }
    }

    cout << min << endl;
}