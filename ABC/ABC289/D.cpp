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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int M;
    cin >> M;
    set<int> B;
    for (int i = 0; i < M; i++)
    {
        int tmp;
        cin >> tmp;
        B.insert(tmp);
    }
    int X;
    cin >> X;

    vector<vector<int>> how;
    int po = pow(2, N);
    int bit = 1;
    for (int i = 0; i < po; i++)
    {
        string r;
        int tmp = bit;
        while (tmp != 0)
        {
            r += (tmp % 2 == 0 ? "0" : "1");
            tmp /= 2;
        }
        vector<int> one;
        int size = r.size();
        int cnt = 0;
        for (int j = 0; j < size; j++)
        {
            if (r[j] == '1')
            {
                one.push_back(j);
                cnt += A[j];
                if (cnt > X)
                {
                    break;
                }
            }
        }
        if (cnt == X)
        {
            how.push_back(one);
        }

        bit++;
    }

    bool ans = false;
    for (auto arr : how)
    {
        int sum = 1;
        for (int i = 1; i <= arr.size(); ++i)
        {
            sum *= i;
        }
        int s;
        int i;
        bool flag = false;
        for (i = 1; i <= sum; i++)
        {
            int a = rand() % arr.size();
            s += arr[a];
            if (B.count(s))
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            ans = true;
            break;
        }
    }
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}