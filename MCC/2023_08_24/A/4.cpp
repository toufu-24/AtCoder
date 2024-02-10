#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

typedef struct node
{
    int val;
    node *next;
    node *prev;
} node;

void insert(node *now, node *new_node)
{
    new_node->next = now->next;
    new_node->prev = now;
    if (now->next != NULL)
        now->next->prev = new_node;
    now->next = new_node;
}

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    node *head = (node *)malloc(sizeof(node));
    node *zero = (node *)malloc(sizeof(node));
    zero->val = 0;
    zero->prev = head;
    zero->next = NULL;
    head->next = zero;
    node *prev = zero;
    for (int i = 0; i < N; i++)
    {
        node *new_node = (node *)malloc(sizeof(node));
        new_node->val = i + 1;
        if (S[i] == 'R')
        {
            insert(prev, new_node);
        }
        else
        {
            insert(prev->prev, new_node);
        }
        prev = new_node;
    }
    while (head->next != NULL)
    {
        cout << head->next->val << " ";
        head = head->next;
    }
}