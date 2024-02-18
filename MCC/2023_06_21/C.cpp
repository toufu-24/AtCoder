#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

typedef enum
{
    add,
    sub,
    num,
} treetype;

typedef struct tree tree;
struct tree
{
    treetype type;
    tree *lhs, *rhs;
    int max, min;
};

tree *expr();
tree *elem();

tree *expr()
{
    tree *e = elem();
}

int main()
{
    while (1)
    {
        string S;
        cin >> S;
        if (S == "-1")
        {
            break;
        }
    }
}