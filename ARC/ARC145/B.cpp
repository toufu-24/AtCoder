#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, A, B;
    cin >> N >> A >> B;
    int count = 0;
    for (int i = A; i <= N; i++)
    {
        int even_odd = 0;
        int tmp = i;
        // 1ずつ確認
        while (true)
        {
            int mini_count = 0;
            //最大まで引く
            while (true)
            {
                if (even_odd % 2 == 0)
                {
                    tmp -= A;
                    if (tmp < 0)
                    {
                        if (mini_count == 0)
                        {
                            break;
                        }
                        tmp += A;
                        break;
                    }
                }
                else
                {
                    tmp -= B;
                    if (tmp < 0)
                    {
                        if (mini_count == 0)
                        {
                            count++;
                            break;
                        }
                        tmp += B;
                        break;
                    }
                }
                mini_count++;
            }
            if (mini_count == 0)
                break;
            even_odd++;
        }
    }
    cout << count << endl;
}