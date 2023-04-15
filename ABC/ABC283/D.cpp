#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_set>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    string S;
    cin >> S;
    int N = S.size();
    stack<int> pre_kakko;
    unordered_set<char> box;
    bool flag = true;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == '(')
        {
            pre_kakko.push(i);
        }
        else if (S[i] == ')')
        {
            for (int j = pre_kakko.top() + 1; j < i; j++)
            {
                if (S[j] >= 'a' && S[j] <= 'z')
                {
                    box.erase(S[j]);
                }
            }
            pre_kakko.pop();
        }
        else
        {
            if (box.count(S[i]))
            {
                cout << "No";
                flag = false;
                break;
            }
            else
            {
                box.insert(S[i]);
            }
        }
    }
    if (flag)
    {
        cout << "Yes";
    }
}